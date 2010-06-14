/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ANDROID_INPUT_H
#define _ANDROID_INPUT_H

/******************************************************************
 *
 * IMPORTANT NOTICE:
 *
 *   This file is part of Android's set of stable system headers
 *   exposed by the Android NDK (Native Development Kit).
 *
 *   Third-party source AND binary code relies on the definitions
 *   here to be FROZEN ON ALL UPCOMING PLATFORM RELEASES.
 *
 *   - DO NOT MODIFY ENUMS (EXCEPT IF YOU ADD NEW 32-BIT VALUES)
 *   - DO NOT MODIFY CONSTANTS OR FUNCTIONAL MACROS
 *   - DO NOT CHANGE THE SIGNATURE OF FUNCTIONS IN ANY WAY
 *   - DO NOT CHANGE THE LAYOUT OR SIZE OF STRUCTURES
 */

/*
 * Structures and functions to receive and process input events in
 * native code.
 *
 * NOTE: These functions MUST be implemented by /system/lib/libui.so
 */

#include <sys/types.h>
#include <android/keycodes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Input device classes.
 */
enum {
    /* The input device is a keyboard. */
    INPUT_DEVICE_CLASS_KEYBOARD      = 0x00000001,

    /* The input device is an alpha-numeric keyboard (not just a dial pad). */
    INPUT_DEVICE_CLASS_ALPHAKEY      = 0x00000002,

    /* The input device is a touchscreen (either single-touch or multi-touch). */
    INPUT_DEVICE_CLASS_TOUCHSCREEN   = 0x00000004,

    /* The input device is a trackball. */
    INPUT_DEVICE_CLASS_TRACKBALL     = 0x00000008,

    /* The input device is a multi-touch touchscreen. */
    INPUT_DEVICE_CLASS_TOUCHSCREEN_MT= 0x00000010,

    /* The input device is a directional pad. */
    INPUT_DEVICE_CLASS_DPAD          = 0x00000020
};

/*
 * Key states (may be returned by queries about the current state of a
 * particular key code, scan code or switch).
 *
 * XXX should we call this BUTTON_STATE_XXX?
 */
enum {
    /* The key state is unknown or the requested key itself is not supported. */
    KEY_STATE_UNKNOWN = -1,

    /* The key is up. */
    KEY_STATE_UP = 0,

    /* The key is down. */
    KEY_STATE_DOWN = 1,

    /* The key is down but is a virtual key press that is being emulated by the system. */
    KEY_STATE_VIRTUAL = 2
};

/*
 * Meta key / modifer state.
 */
enum {
    /* No meta keys are pressed. */
    META_NONE = 0,

    /* This mask is used to check whether one of the ALT meta keys is pressed. */
    META_ALT_ON = 0x02,

    /* This mask is used to check whether the left ALT meta key is pressed. */
    META_ALT_LEFT_ON = 0x10,

    /* This mask is used to check whether the right ALT meta key is pressed. */
    META_ALT_RIGHT_ON = 0x20,

    /* This mask is used to check whether one of the SHIFT meta keys is pressed. */
    META_SHIFT_ON = 0x01,

    /* This mask is used to check whether the left SHIFT meta key is pressed. */
    META_SHIFT_LEFT_ON = 0x40,

    /* This mask is used to check whether the right SHIFT meta key is pressed. */
    META_SHIFT_RIGHT_ON = 0x80,

    /* This mask is used to check whether the SYM meta key is pressed. */
    META_SYM_ON = 0x04
};

/*
 * Input events.
 *
 * Input events are opaque structures.  Use the provided accessors functions to
 * read their properties.
 */
struct input_event_t;
typedef struct input_event_t input_event_t;

/*
 * Input event types.
 */
enum {
    /* Indicates that the input event is a key event. */
    INPUT_EVENT_TYPE_KEY = 1,

    /* Indicates that the input event is a motion event. */
    INPUT_EVENT_TYPE_MOTION = 2
};

/*
 * Key event actions.
 */
enum {
    /* The key has been pressed down. */
    KEY_EVENT_ACTION_DOWN = 0,

    /* The key has been released. */
    KEY_EVENT_ACTION_UP = 1,

    /* Multiple duplicate key events have occurred in a row, or a complex string is
     * being delivered.  The repeat_count property of the key event contains the number
     * of times the given key code should be executed.
     */
    KEY_EVENT_ACTION_MULTIPLE = 2
};

/*
 * Key event flags.
 */
enum {
    /* This mask is set if the device woke because of this key event. */
    KEY_EVENT_FLAG_WOKE_HERE = 0x1,

    /* This mask is set if the key event was generated by a software keyboard. */
    KEY_EVENT_FLAG_SOFT_KEYBOARD = 0x2,

    /* This mask is set if we don't want the key event to cause us to leave touch mode. */
    KEY_EVENT_FLAG_KEEP_TOUCH_MODE = 0x4,

    /* This mask is set if an event was known to come from a trusted part
     * of the system.  That is, the event is known to come from the user,
     * and could not have been spoofed by a third party component. */
    KEY_EVENT_FLAG_FROM_SYSTEM = 0x8,

    /* This mask is used for compatibility, to identify enter keys that are
     * coming from an IME whose enter key has been auto-labelled "next" or
     * "done".  This allows TextView to dispatch these as normal enter keys
     * for old applications, but still do the appropriate action when
     * receiving them. */
    KEY_EVENT_FLAG_EDITOR_ACTION = 0x10,

    /* When associated with up key events, this indicates that the key press
     * has been canceled.  Typically this is used with virtual touch screen
     * keys, where the user can slide from the virtual key area on to the
     * display: in that case, the application will receive a canceled up
     * event and should not perform the action normally associated with the
     * key.  Note that for this to work, the application can not perform an
     * action for a key until it receives an up or the long press timeout has
     * expired. */
    KEY_EVENT_FLAG_CANCELED = 0x20,

    /* This key event was generated by a virtual (on-screen) hard key area.
     * Typically this is an area of the touchscreen, outside of the regular
     * display, dedicated to "hardware" buttons. */
    KEY_EVENT_FLAG_VIRTUAL_HARD_KEY = 0x40,

    /* This flag is set for the first key repeat that occurs after the
     * long press timeout. */
    KEY_EVENT_FLAG_LONG_PRESS = 0x80,

    /* Set when a key event has KEY_EVENT_FLAG_CANCELED set because a long
     * press action was executed while it was down. */
    KEY_EVENT_FLAG_CANCELED_LONG_PRESS = 0x100,

    /* Set for KEY_EVENT_ACTION_UP when this event's key code is still being
     * tracked from its initial down.  That is, somebody requested that tracking
     * started on the key down and a long press has not caused
     * the tracking to be canceled. */
    KEY_EVENT_FLAG_TRACKING = 0x200
};

/*
 * Motion event actions.
 */

/* Bit shift for the action bits holding the pointer index as
 * defined by MOTION_EVENT_ACTION_POINTER_INDEX_MASK.
 */
#define MOTION_EVENT_ACTION_POINTER_INDEX_SHIFT 8

enum {
    /* Bit mask of the parts of the action code that are the action itself.
     */
    MOTION_EVENT_ACTION_MASK = 0xff,

    /* Bits in the action code that represent a pointer index, used with
     * MOTION_EVENT_ACTION_POINTER_DOWN and MOTION_EVENT_ACTION_POINTER_UP.  Shifting
     * down by MOTION_EVENT_ACTION_POINTER_INDEX_SHIFT provides the actual pointer
     * index where the data for the pointer going up or down can be found.
     */
    MOTION_EVENT_ACTION_POINTER_INDEX_MASK  = 0xff00,

    /* A pressed gesture has started, the motion contains the initial starting location.
     */
    MOTION_EVENT_ACTION_DOWN = 0,

    /* A pressed gesture has finished, the motion contains the final release location
     * as well as any intermediate points since the last down or move event.
     */
    MOTION_EVENT_ACTION_UP = 1,

    /* A change has happened during a press gesture (between MOTION_EVENT_ACTION_DOWN and
     * MOTION_EVENT_ACTION_UP).  The motion contains the most recent point, as well as
     * any intermediate points since the last down or move event.
     */
    MOTION_EVENT_ACTION_MOVE = 2,

    /* The current gesture has been aborted.
     * You will not receive any more points in it.  You should treat this as
     * an up event, but not perform any action that you normally would.
     */
    MOTION_EVENT_ACTION_CANCEL = 3,

    /* A movement has happened outside of the normal bounds of the UI element.
     * This does not provide a full gesture, but only the initial location of the movement/touch.
     */
    MOTION_EVENT_ACTION_OUTSIDE = 4,

    /* A non-primary pointer has gone down.
     * The bits in MOTION_EVENT_ACTION_POINTER_INDEX_MASK indicate which pointer changed.
     */
    MOTION_EVENT_ACTION_POINTER_DOWN = 5,

    /* A non-primary pointer has gone up.
     * The bits in MOTION_EVENT_ACTION_POINTER_INDEX_MASK indicate which pointer changed.
     */
    MOTION_EVENT_ACTION_POINTER_UP = 6
};

/*
 * Motion event edge touch flags.
 */
enum {
    /* No edges intersected */
    MOTION_EVENT_EDGE_FLAG_NONE = 0,

    /* Flag indicating the motion event intersected the top edge of the screen. */
    MOTION_EVENT_EDGE_FLAG_TOP = 0x01,

    /* Flag indicating the motion event intersected the bottom edge of the screen. */
    MOTION_EVENT_EDGE_FLAG_BOTTOM = 0x02,

    /* Flag indicating the motion event intersected the left edge of the screen. */
    MOTION_EVENT_EDGE_FLAG_LEFT = 0x04,

    /* Flag indicating the motion event intersected the right edge of the screen. */
    MOTION_EVENT_EDGE_FLAG_RIGHT = 0x08
};

/*
 * Specifies the logical nature of an input event.
 * For example, the nature distinguishes between motion events that represent touches and
 * those that represent trackball moves.
 *
 * XXX This concept is tentative.  Another idea would be to associate events with logical
 *     controllers rather than physical devices.   The interpretation of an event would
 *     be made with respect to the nature of the controller that is considered the logical
 *     source of an event.  The decoupling is beneficial since multiple physical (and virtual)
 *     devices could be responsible for producing events that would be associated with
 *     various logical controllers.  For example, the hard keyboard, on screen keyboard,
 *     and peripheral keyboard could be mapped onto a single logical "keyboard" controller
 *     (or treated independently, if desired).
 */
enum {
    INPUT_EVENT_NATURE_KEY = 1,
    INPUT_EVENT_NATURE_TOUCH = 2,
    INPUT_EVENT_NATURE_TRACKBALL = 3
};

/*
 * Input event accessors.
 *
 * Note that most functions can only be used on input events that are of a given type.
 * Calling these functions on input events of other types will yield undefined behavior.
 */

/*** Accessors for all input events. ***/

/* Get the input event type. */
int32_t input_event_get_type(const input_event_t* event);

/* Get the id for the device that an input event came from.
 *
 * Input events can be generated by multiple different input devices.
 * Use the input device id to obtain information about the input
 * device that was responsible for generating a particular event.
 *
 * An input device id of 0 indicates that the event didn't come from a physical device;
 * other numbers are arbitrary and you shouldn't depend on the values.
 * Use the provided input device query API to obtain information about input devices.
 */
int32_t input_event_get_device_id(const input_event_t* event);

/* Get the input event nature. */
int32_t input_event_get_nature(const input_event_t* event);

/*** Accessors for key events only. ***/

/* Get the key event action. */
int32_t key_event_get_action(const input_event_t* key_event);

/* Get the key event flags. */
int32_t key_event_get_flags(const input_event_t* key_event);

/* Get the key code of the key event.
 * This is the physical key that was pressed, not the Unicode character. */
int32_t key_event_get_key_code(const input_event_t* key_event);

/* Get the hardware key id of this key event.
 * These values are not reliable and vary from device to device. */
int32_t key_event_get_scan_code(const input_event_t* key_event);

/* Get the meta key state. */
int32_t key_event_get_meta_state(const input_event_t* key_event);

/* Get the repeat count of the event.
 * For both key up an key down events, this is the number of times the key has
 * repeated with the first down starting at 0 and counting up from there.  For
 * multiple key events, this is the number of down/up pairs that have occurred. */
int32_t key_event_get_repeat_count(const input_event_t* key_event);

/* Get the time of the most recent key down event, in the
 * java.lang.System.nanoTime() time base.  If this is a down event,
 * this will be the same as eventTime.
 * Note that when chording keys, this value is the down time of the most recently
 * pressed key, which may not be the same physical key of this event. */
int64_t key_event_get_down_time(const input_event_t* key_event);

/* Get the time this event occurred, in the
 * java.lang.System.nanoTime() time base. */
int64_t key_event_get_event_time(const input_event_t* key_event);

/*** Accessors for motion events only. ***/

/* Get the combined motion event action code and pointer index. */
int32_t motion_event_get_action(const input_event_t* motion_event);

/* Get the state of any meta / modifier keys that were in effect when the
 * event was generated. */
int32_t motion_event_get_meta_state(const input_event_t* motion_event);

/* Get a bitfield indicating which edges, if any, were touched by this motion event.
 * For touch events, clients can use this to determine if the user's finger was
 * touching the edge of the display. */
int32_t motion_event_get_edge_flags(const input_event_t* motion_event);

/* Get the time when the user originally pressed down to start a stream of
 * position events, in the java.lang.System.nanoTime() time base. */
int64_t motion_event_get_down_time(const input_event_t* motion_event);

/* Get the time when this specific event was generated,
 * in the java.lang.System.nanoTime() time base. */
int64_t motion_event_get_event_time(const input_event_t* motion_event);

/* Get the precision of the X coordinates being reported.
 * You can multiply this number with an X coordinate sample to find the
 * actual hardware value of the X coordinate. */
float motion_event_get_x_precision(const input_event_t* motion_event);

/* Get the precision of the Y coordinates being reported.
 * You can multiply this number with a Y coordinate sample to find the
 * actual hardware value of the Y coordinate. */
float motion_event_get_y_precision(const input_event_t* motion_event);

/* Get the number of pointers of data contained in this event.
 * Always >= 1. */
size_t motion_event_get_pointer_count(const input_event_t* motion_event);

/* Get the pointer identifier associated with a particular pointer
 * data index is this event.  The identifier tells you the actual pointer
 * number associated with the data, accounting for individual pointers
 * going up and down since the start of the current gesture. */
int32_t motion_event_get_pointer_id(const input_event_t* motion_event, size_t pointer_index);

/* Get the original raw X coordinate of this event.  For touch
 * events on the screen, this is the original location of the event
 * on the screen, before it had been adjusted for the containing window
 * and views. */
float motion_event_get_raw_x(const input_event_t* motion_event);

/* Get the original raw X coordinate of this event.  For touch
 * events on the screen, this is the original location of the event
 * on the screen, before it had been adjusted for the containing window
 * and views. */
float motion_event_get_raw_y(const input_event_t* motion_event);

/* Get the current X coordinate of this event for the given pointer index.
 * Whole numbers are pixels; the value may have a fraction for input devices
 * that are sub-pixel precise. */
float motion_event_get_x(const input_event_t* motion_event, size_t pointer_index);

/* Get the current Y coordinate of this event for the given pointer index.
 * Whole numbers are pixels; the value may have a fraction for input devices
 * that are sub-pixel precise. */
float motion_event_get_y(const input_event_t* motion_event, size_t pointer_index);

/* Get the current pressure of this event for the given pointer index.
 * The pressure generally ranges from 0 (no pressure at all) to 1 (normal pressure),
 * however values higher than 1 may be generated depending on the calibration of
 * the input device. */
float motion_event_get_pressure(const input_event_t* motion_event, size_t pointer_index);

/* Get the current scaled value of the approximate size for the given pointer index.
 * This represents some approximation of the area of the screen being
 * pressed; the actual value in pixels corresponding to the
 * touch is normalized with the device specific range of values
 * and scaled to a value between 0 and 1.  The value of size can be used to
 * determine fat touch events. */
float motion_event_get_size(const input_event_t* motion_event, size_t pointer_index);

/* Get the number of historical points in this event.  These are movements that
 * have occurred between this event and the previous event.  This only applies
 * to MOTION_EVENT_ACTION_MOVE events -- all other actions will have a size of 0.
 * Historical samples are indexed from oldest to newest. */
size_t motion_event_get_history_size(const input_event_t* motion_event);

/* Get the time that a historical movement occurred between this event and
 * the previous event, in the java.lang.System.nanoTime() time base. */
int64_t motion_event_get_historical_event_time(input_event_t* motion_event,
        size_t history_index);

/* Get the historical X coordinate of this event for the given pointer index that
 * occurred between this event and the previous motion event.
 * Whole numbers are pixels; the value may have a fraction for input devices
 * that are sub-pixel precise. */
float motion_event_get_historical_x(input_event_t* motion_event, size_t pointer_index,
        size_t history_index);

/* Get the historical Y coordinate of this event for the given pointer index that
 * occurred between this event and the previous motion event.
 * Whole numbers are pixels; the value may have a fraction for input devices
 * that are sub-pixel precise. */
float motion_event_get_historical_y(input_event_t* motion_event, size_t pointer_index,
        size_t history_index);

/* Get the historical pressure of this event for the given pointer index that
 * occurred between this event and the previous motion event.
 * The pressure generally ranges from 0 (no pressure at all) to 1 (normal pressure),
 * however values higher than 1 may be generated depending on the calibration of
 * the input device. */
float motion_event_get_historical_pressure(input_event_t* motion_event, size_t pointer_index,
        size_t history_index);

/* Get the current scaled value of the approximate size for the given pointer index that
 * occurred between this event and the previous motion event.
 * This represents some approximation of the area of the screen being
 * pressed; the actual value in pixels corresponding to the
 * touch is normalized with the device specific range of values
 * and scaled to a value between 0 and 1.  The value of size can be used to
 * determine fat touch events. */
float motion_event_get_historical_size(input_event_t* motion_event, size_t pointer_index,
        size_t history_index);

#ifdef __cplusplus
}
#endif

#endif // _ANDROID_INPUT_H
