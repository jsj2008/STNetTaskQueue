//
//  STHTTPNetTask.h
//  STNetTaskQueue
//
//  Created by Kevin Lin on 29/11/14.
//  Copyright (c) 2014 Sth4Me. All rights reserved.
//

#import <STNetTaskQueue/STNetTask.h>

NS_ASSUME_NONNULL_BEGIN

// Error domains
FOUNDATION_EXPORT NSString *const STHTTPNetTaskServerError;
FOUNDATION_EXPORT NSString *const STHTTPNetTaskResponseParsedError;

// Error "userInfo" keys
FOUNDATION_EXPORT NSString *const STHTTPNetTaskErrorStatusCodeUserInfoKey DEPRECATED_MSG_ATTRIBUTE("Use STHTTPNetTask.statusCode instead");
FOUNDATION_EXPORT NSString *const STHTTPNetTaskErrorResponseDataUserInfoKey;

FOUNDATION_EXPORT NSString *STHTTPNetTaskRequestObjectDefaultSeparator;

#define STHTTPNetTaskIgnoreAllProperties @[ @"*" ]

typedef NS_ENUM(NSUInteger, STHTTPNetTaskMethod) {
    STHTTPNetTaskGet,
    STHTTPNetTaskPost,
    STHTTPNetTaskPut,
    STHTTPNetTaskDelete,
    STHTTPNetTaskHead,
    STHTTPNetTaskPatch
};

typedef NS_ENUM(NSUInteger, STHTTPNetTaskRequestType) {
    STHTTPNetTaskRequestJSON,
    STHTTPNetTaskRequestKeyValueString,
    STHTTPNetTaskRequestFormData
};

typedef NS_ENUM(NSUInteger, STHTTPNetTaskResponseType) {
    STHTTPNetTaskResponseJSON,
    STHTTPNetTaskResponseString,
    STHTTPNetTaskResponseRawData
};

/**
 STIgnore marks a property as "ignore" so that the property will be ignored when packing the request.
 STHTTPNetTaskRequestObject-ignoredProperties will do the same.
 
 @see STHTTPNetTaskRequestObject
 */
@protocol STIgnore

@end

/**
 To avoid complier warnings
 */
@interface NSObject (STHTTPNetTaskRequestObject) <STIgnore>

@end

/**
 If a class conforms to this protocol, it means the instance of this class will be converted to a dictionary and passed as parameter in a HTTP request.
 */
@protocol STHTTPNetTaskRequestObject <NSObject>

/**
 Properties which should be ignored when packing parameters for reqeust.
 
 @return NSArray<NSString> An array of strings representing the name of properties to be ignored.
 */
- (NSArray<NSString *> *)ignoredProperties;

@optional

/**
 Transform a value to another.
 Use case: NSArray need to be transformed to comma separated string.
 
 @param value id Value to be transformed
 @return id The transformed value. Should return the same value if "value" is not supposed to be transformed.
 */
- (nullable id)transformValue:(id)value;

/**
 Separator string which should be used when packing parameters.
 E.g. property schoolName will be converted to school_name.
 Default: @"_"
 
 @return NSString
 */
- (nullable NSString *)parameterNameSeparator;

@end

/**
 Net task which is designed for HTTP protocol.
 */
@interface STHTTPNetTask : STNetTask<STHTTPNetTaskRequestObject>

/**
 HTTP status code.
 */
@property (atomic, assign, readonly) NSInteger statusCode;

/**
 HTTP headers of response.
 */
@property (atomic, strong, readonly) NSDictionary *responseHeaders;

/**
 HTTP method which should be used for the HTTP net task.
 
 @return STHTTPNetTaskMethod
 */
- (STHTTPNetTaskMethod)method;

/**
 Request parameters format. E.g JSON, key-value string(form param).
 
 @return STHTTPNetTaskRequestType
 */
- (STHTTPNetTaskRequestType)requestType;

/**
 Response data format. E.g JSON, String, Raw data.
 
 @return STHTTPNetTaskResponseType
 */
- (STHTTPNetTaskResponseType)responseType;

/**
 Custom headers which will be added into HTTP request headers.
 
 @return NSDictionary<NSString, NSString> Custom headers, e.g. @{ @"User-Agent": @"STNetTaskQueue Client" }
 */
- (NSDictionary<NSString *, NSString *> *)headers;

/**
 Additional parameters which will be added as HTTP request parameters.
 
 @return NSDictionary<NSString, id>
 */
- (NSDictionary<NSString *, id> *)parameters;

/**
 NSDatas which will be added into multi-part form data body,
 requestType should be STHTTPNetTaskRequestFormData if you are going to return datas.
 
 @return NSDictionary<NSString, NSData>
 */
- (NSDictionary<NSString *, NSData *> *)datas;

/**
 This method will be called if the response object is a dictionary.
 
 @param dictionary NSDictionary
 */
- (void)didResponseDictionary:(NSDictionary *)dictionary;

/**
 This method will be called if the response object is an array.
 
 @param array NSArray
 */
- (void)didResponseArray:(NSArray *)array;

/**
 This method will be called if the response obejct is a string.
 
 @param string NSString
 */
- (void)didResponseString:(NSString *)string;

/**
 This method will be called if the response object is NSData
 
 @param data NSData
 */
- (void)didResponseData:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
