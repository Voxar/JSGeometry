#ifndef JSGeometry
#define JSGeometry

#import <CoreGraphics/CGGeometry.h>

#pragma mark - Enums

/**
 *  Enum describing various alignments
 *
 *  @discussion Multiple values may be combined in a bitmask
 */
typedef enum : NSUInteger {
    JSGRectAlignmentTop = 1,
    JSGRectAlignmentRight = 1 << 1,
    JSGRectAlignmentBottom = 1 << 2,
    JSGRectAlignmentLeft = 1 << 3
} JSGRectAlignment;

/**
 *  Enum describing various coordinate system origins used
 *  on Apple platforms
 */
typedef enum : NSUInteger {
    JSGCoordinateSystemOriginTopLeft,
    JSGCoordinateSystemOriginBottomLeft
} JSGCoordinateSystemOrigin;

#pragma mark - CGPoint functions

/**
 *  Return the integral point for a given point
 *
 *  @param point The point to get the integral point for
 *
 *  @discussion The point's x & y components will be rounded
 *  to their closest non-fractional value.
 */
CG_INLINE CGPoint JSGPointIntegral(CGPoint point)
{
    point.x = roundf(point.x);
    point.y = roundf(point.y);
    
    return point;
}

/**
 *  Return the center point for a size when placed within another size
 *
 *  @param sizeA The size that will be placed within the other size
 *  @param sizeB The size in which sizeA will be placed
 *
 *  @discussion This function always returns the integral result of
 *  the generated point.
 */
CG_INLINE CGPoint JSGCenterPointForSizeInSize(CGSize sizeA, CGSize sizeB)
{
    CGPoint centerPoint;
    
    centerPoint.x = (sizeB.width - sizeA.width) / 2;
    centerPoint.y = (sizeB.height - sizeA.height) / 2;
    
    return JSGPointIntegral(centerPoint);
}

#pragma mark - CGSize functions

/**
 *  Return the integral size for a given size
 *
 *  @param size The size to get the integral point for
 *
 *  @discussion The size's width & height components will be
 *  rounded to their closest non-fractional value.
 */
CG_INLINE CGSize JSGSizeIntegral(CGSize size)
{
    size.width = roundf(size.width);
    size.height = roundf(size.height);
    
    return size;
}

/**
 *  Scale a size
 *
 *  @param size The size that should be scaled
 *  @param scaleX The horizontal scale to apply
 *  @param scaleY The vertical scale to apply
 *
 *  @discussion This function always returns the integral result of
 *  the scaled size.
 */
CG_INLINE CGSize JSGSizeScale(CGSize size, CGFloat scaleX, CGFloat scaleY)
{
    size.width *= scaleX;
    size.height *= scaleY;
    
    return JSGSizeIntegral(size);
}

#pragma mark - CGRect functions

/**
 *  Change the origin of a rect
 *
 *  @param rect The rect to change
 *  @param newOrigin The new origin that the rect should have
 */
CG_INLINE CGRect JSGRectChangeOrigin(CGRect rect, CGPoint newOrigin)
{
    rect.origin = newOrigin;
    
    return rect;
}

/**
 *  Change the x component of a rect's origin
 *
 *  @param rect The rect to change
 *  @param newOriginX The new x component that the rect's origin should have
 */
CG_INLINE CGRect JSGRectChangeOriginX(CGRect rect, CGFloat newOriginX)
{
    rect.origin.x = newOriginX;
    
    return rect;
}

/**
 *  Change the y component of a rect's origin
 *
 *  @param rect The rect to change
 *  @param newOriginY The new y component that the rect's origin should have
 */
CG_INLINE CGRect JSGRectChangeOriginY(CGRect rect, CGFloat newOriginY)
{
    rect.origin.y = newOriginY;
    
    return rect;
}

/**
 *  Change the size of a rect
 *
 *  @param rect The rect to change
 *  @param newSize The new size that the rect should have
 */
CG_INLINE CGRect JSGRectChangeSize(CGRect rect, CGSize newSize)
{
    rect.size = newSize;
    
    return rect;
}

/**
 *  Change the width of a rect
 *
 *  @param rect The rect to change
 *  @param newSize The new width that the rect should have
 */
CG_INLINE CGRect JSGRectChangeWidth(CGRect rect, CGFloat newWidth)
{
    rect.size.width = newWidth;
    
    return rect;
}

/**
 *  Change the height of a rect
 *
 *  @param rect The rect to change
 *  @param newSize The new height that the rect should have
 */
CG_INLINE CGRect JSGRectChangeHeight(CGRect rect, CGFloat newHeight)
{
    rect.size.height = newHeight;
    
    return rect;
}

/**
 *  Scale a rect's size
 *
 *  @param rect The rect that should be scaled
 *  @param scaleX The horizontal scale to apply
 *  @param scaleY The vertical scale to apply
 *
 *  @discussion This function always returns the integral rect for the
 *  generated rect.
 */
CG_INLINE CGRect JSGRectScale(CGRect rect, CGFloat scaleX, CGFloat scaleY)
{
    rect.size = JSGSizeScale(rect.size, scaleX, scaleY);
    
    return CGRectIntegral(rect);
}

/**
 *  Center a rect within another rect
 *
 *  @param rectA The rect to center in the other rect
 *  @param rectB The rect in which rectA will be centered
 *
 *  @discussion This function always returns the integral rect for the
 *  generated rect.
 */
CG_INLINE CGRect JSGRectGetCenterInRect(CGRect rectA, CGRect rectB)
{
    rectA.origin = JSGCenterPointForSizeInSize(rectA.size, rectB.size);
    
    return rectA;
}

/**
 *  Align a rect within another rect, according to a coordinate system origin
 *
 *  @param rectA The rect to center in the other rect
 *  @param rectB The rect in which rectA will be centered
 *  @param alignment The alignment that should be applied to rectA. Multiple alignments
 *  may be combined in a bitmask. If the supplied bitmask contains both a top & bottom
 *  alignment, then only the bottom one will be used. If it contains both a left & right one,
 *  then only the right one will be used.
 *  @param coordinateSystemOrigin The origin of the used coordinate system
 *
 *  @discussion For a simpler version of this function, see JSGRectAlignInRect.
 *
 *  @see JSRectAlignment, JSGCoordinateSystemOrigin
 */
CG_INLINE CGRect JSGRectAlignInRectForCoordinateSystemOrigin(CGRect rectA, CGRect rectB, JSGRectAlignment alignment, JSGCoordinateSystemOrigin coordinateSystemOrigin)
{
    if (alignment & JSGRectAlignmentTop) {
        switch (coordinateSystemOrigin) {
            case JSGCoordinateSystemOriginTopLeft:
                rectA.origin.y = 0;
                break;
            case JSGCoordinateSystemOriginBottomLeft:
                rectA.origin.y = CGRectGetHeight(rectB) - CGRectGetHeight(rectA);
                break;
        }
    }
    
    if (alignment & JSGRectAlignmentLeft) {
        rectA.origin.x = 0;
    }
    
    if (alignment & JSGRectAlignmentBottom) {
        switch (coordinateSystemOrigin) {
            case JSGCoordinateSystemOriginTopLeft:
                rectA.origin.y = CGRectGetHeight(rectB) - CGRectGetHeight(rectA);
                break;
            case JSGCoordinateSystemOriginBottomLeft:
                rectA.origin.y = 0;
                break;
        }
    }
    
    if (alignment & JSGRectAlignmentRight) {
        rectA.origin.x = CGRectGetWidth(rectB) - CGRectGetWidth(rectA);
    }
    
    return rectA;
}

/**
 *  Align a rect within another rect, according to a coordinate system origin
 *
 *  @param rectA The rect to center in the other rect
 *  @param rectB The rect in which rectA will be centered
 *  @param alignment The alignment that should be applied to rectA. Multiple alignments
 *  may be combined in a bitmask. If the supplied bitmask contains both a top & bottom
 *  alignment, then only the bottom one will be used. If it contains both a left & right one,
 *  then only the right one will be used.
 *
 *  @discussion This function attempts to guess the origin of the currently used coordinate system,
 *  judging on which platform the code was compiled for. For OSX, a bottom/left coordinate system
 *  origin is assumed, and for iOS a top/left one is assumed. When using a coordinate system with
 *  an origin other than the default/assumed one, please use the JSGRectAlignInRectForCoordinateSystemOrigin
 *  function instead, that lets you specify what coordinate system origin to use.
 */
CG_INLINE CGRect JSGRectAlignInRect(CGRect rectA, CGRect rectB, JSGRectAlignment alignment)
{
#if TARGET_OS_IPHONE
    return JSGRectAlignInRectForCoordinateSystemOrigin(rectA, rectB, alignment, JSGCoordinateSystemOriginTopLeft);
#else
    return JSGRectAlignInRectForCoordinateSystemOrigin(rectA, rectB, alignment, JSGCoordinateSystemOriginBottomLeft);
#endif
}

#endif
