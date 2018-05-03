/**
  @file conbtdialogs-dbus.h

  Copyright (C) 2006, 2009, Nokia Corporation

  @author Aapo Makela <aapo.makela@nokia.com>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License version 2.1 as
  published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser
  General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this library; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/**
  Example of use (command line):

  dbus-send --system --print-reply \
    --dest='com.nokia.icd_ui' /com/nokia/bt_ui \
    com.nokia.bt_ui.show_send_file_dlg \
    array:string:file:///home/user/MyDocs/.documents/testing.txt

  dbus-send --system --print-reply \
    --dest=com.nokia.bt_ui  /com/nokia/bt_ui
    com.nokia.bt_ui.show_search_dlg \
    string: string: array:string: string:
*/

#ifndef CONBTDIALOGS_DBUS_H
#define CONBTDIALOGS_DBUS_H

#ifdef __cplusplus
extern "C" {
#endif

/** Conbtdialogs service, resides in system dbus */
#define CONBTDIALOGS_DBUS_SERVICE   "com.nokia.bt_ui"
/** Conbtdialogs interface */
#define CONBTDIALOGS_DBUS_INTERFACE "com.nokia.bt_ui"
/** Conbtdialogs path */
#define CONBTDIALOGS_DBUS_PATH      "/com/nokia/bt_ui"

/**
  Show send file dialog

  Arguments:

  uris: DBUS_TYPE_ARRAY         Array of strings representing the URIs of the
                                files to send.

  Returns:

  DBUS_TYPE_BOOLEAN             TRUE, if dialog was shown succesfully.
 */
#define CONBTDIALOGS_SEND_FILE_REQ  "show_send_file_dlg"

/**
  File sending result signal

  Arguments:

  success: DBUS_TYPE_BOOLEAN  TRUE, if all files were sent succesful or
                                FALSE, if error occured or sending was
                                cancelled.
 */
#define CONBTDIALOGS_SEND_FILE_SIG  "send_file"

/**
  Show BT device search dialog

  Arguments:

  major_class: DBUS_TYPE_STRING To set filtering based on major_class or
                                "". Possible major class values are:

                                "miscellaneous", "computer", "phone",
                                "access point", "audio/video",
                                "peripheral", "imaging", "wearable",
                                "toy" and "uncategorized".

  minor_class: DBUS_TYPE_STRING To set filtering based on minor_class or "".
                                Possible minor class values are:

                                - Minor classes for "computer":
                                  "uncategorized", "desktop", "server",
                                  "laptop", "handheld", "palm", "wearable"

                                - Minor classes for "phone": "uncategorized",
                                  "cellular", "cordless", "smart phone",
                                  "modem", "isdn"

  service_classes: DBUS_TYPE_ARRAY To set filtering based on service classes.
                                   Supported classes include "positioning",
                                   "networking", "rendering", "capturing",
                                   "object transfer", "audio", "telephony",
                                   "information". Can be empty list, when no
                                   service class filtering is performed.

  bonding: DBUS_TYPE_STRING     Bonding mode for found and selected device:

                                "require" for requiring a bonding from a
                                selected device (i.e. bond device if it hasn't
                                been bond before).

                                "force" to always bond (i.e. device will be
                                bond even if bonded before).

                                Any other string will allow to search and
                                select device without bonding it.

  Returns:

  DBUS_TYPE_BOOLEAN             TRUE, if dialog was shown succesfully.
 */
#define CONBTDIALOGS_SEARCH_REQ     "show_search_dlg"

/**
  Bluetooth search result signal

  Arguments:

  address: DBUS_TYPE_STRING     Bluetooth address of the selected device or ""
                                if search dialog was cancelled.

  name: DBUS_TYPE_STRING        Name of the device.

  icon: DBUS_TYPE_STRING        Logical name for the icon describing the
                                device.

  major_class: DBUS_TYPE_STRING Major class of the device.

  minor_class: DBUS_TYPE_STRING Minor class of the device.

  trusted: DBUS_TYPE_BOOLEAN    If device is marked as trusted device

  services: DBUS_TYPE_ARRAY     List of strings describing the service classes
                                and SDP based services provided by the device.
 */
#define CONBTDIALOGS_SEARCH_SIG     "search_result"


#ifdef __cplusplus
}
#endif

#endif

