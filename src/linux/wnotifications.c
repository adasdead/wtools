#include "wtools/wnotifications.h"

#include <gio/gio.h>
#include <stdio.h>

#define W_APPLICATION_ID "com.adasdead.wtools"

w_result_t w_notifications_notify(w_castr_t message,
                                  w_castr_t title)
{
    GApplication *application;
    application = g_application_new(W_APPLICATION_ID,
                                    G_APPLICATION_FLAGS_NONE);

	if (g_application_register(application, NULL, NULL))
    {
        GNotification *notification = g_notification_new(title);
        g_notification_set_body(notification, message);

        g_application_send_notification(application, NULL, notification);

        g_object_unref(notification);

        return W_OK;
    }

    return W_ERR;
}