/**
 * WPBannerView.h
 *
 * Copyright (c) 2010, Alexey Goliatin <alexey.goliatin@gmail.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright notice, 
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *   * Neither the name of the "Wapstart" nor the names of its contributors 
 *     may be used to endorse or promote products derived from this software 
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <UIKit/UIKit.h>
#import <Accounts/Accounts.h>
#import "WPBannerInfoLoader.h"
#import "WPInitRequestLoader.h"
#import "WPLocationManager.h"
#import "MRAdView.h"
#import "WPAdView.h"

@class WPBannerInfo;
@protocol WPBannerViewDelegate;

@interface WPBannerView : UIView <WPBannerInfoLoaderDelegate, WPInitRequestLoaderDelegate, WPLocationManagerDelegate, MRAdViewDelegate, WPAdViewDelegate>
{
	WPBannerRequestInfo *_bannerRequestInfo;
	WPBannerInfoLoader  *_bannerInfoLoader;
	WPInitRequestLoader *_initRequestLoader;
    WPLocationManager   *_locationManager;

	NSString			*_callbackUrl;

	UIView				*_currentContentView;

	CGFloat _autoupdateTimeout;
	NSTimer *_autoupdateTimer;
	CGFloat _reinitTimeout;
	NSTimer *_reinitTimer;
	CGFloat _facebookInfoUpdateTimeout;
	NSTimer *_facebookInfoUpdateTimer;
	CGFloat _twitterInfoUpdateTimeout;
	NSTimer *_twitterInfoUpdateTimer;

	UIInterfaceOrientation _orientation;
	UIActivityIndicatorView *_loadingInfoIndicator;
	UIButton *_closeButton;
	BOOL _showCloseButton;
	BOOL _isExpanded;

	CGRect _hiddenBannerFrame;
	CGRect _visibleBannerFrame;

	id<WPBannerViewDelegate> _delegate;
	
	NSMutableData   *_imageData;
	NSUInteger      _imageSize;
	NSMutableSet	*_adviewPool;

	BOOL _isMinimized;
	NSString *_minimizedLabel;

    BOOL _disableAutoDetectLocation;

	NSMutableDictionary *_backupValueDictionary;
	BOOL _openInBrowser;
}

@property (nonatomic, assign) BOOL showCloseButton;
@property (nonatomic, assign) CGFloat autoupdateTimeout;
@property (nonatomic, assign) BOOL isMinimized;
@property (nonatomic, retain) NSString *minimizedLabel;
@property (nonatomic, readonly) BOOL isEmpty;
@property (nonatomic, readonly) CGFloat bannerHeight;
@property (nonatomic, assign) BOOL disableAutoDetectLocation;
@property (nonatomic, assign) UIInterfaceOrientation orientation;
@property (nonatomic, assign) CGFloat reinitTimeout;
@property (nonatomic, assign) CGFloat facebookInfoUpdateTimeout;
@property (nonatomic, assign) CGFloat twitterInfoUpdateTimeout;
@property (nonatomic, assign) BOOL openInBrowser;

@property (nonatomic, assign) id<WPBannerViewDelegate> delegate;

- (id) initWithBannerRequestInfo:(WPBannerRequestInfo *) requestInfo andCallbackUrl:(NSString *) callbackUrl;

- (void) showFromTop:(BOOL) animated;
- (void) showFromBottom:(BOOL) animated;

- (void) hide:(BOOL) animated;

- (void) reloadBanner;

- (void) setIsMinimized:(BOOL)minimize animated:(BOOL) animated;

@end


@protocol WPBannerViewDelegate <NSObject>

@optional

- (void) bannerViewPressed:(WPBannerView *) bannerView;

- (void) bannerViewInfoLoaded:(WPBannerView *) bannerView;
- (void) bannerViewInfoDidFailWithError:(WPBannerInfoLoaderErrorCode) errorCode;

- (void) bannerViewDidHide:(WPBannerView *) bannerView;
- (void) bannerViewMinimizedStateWillChange:(WPBannerView *) bannerView;
- (void) bannerViewMinimizedStateChanged:(WPBannerView *) bannerView;

@end