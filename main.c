#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "views.h"
#include "webview/webview.h"

const bool DEBUG = true;

typedef struct
{
    webview_t w;
    long count;
} context_t;

/*
 * a command that can be called from frontend.
 * @param id: an uid for the request
 * @param req: a req? not yet sure TODO: found out what req is
 * @param arg: arg from the binding-time, here context in ll 77
 *
 * workings: (my understanding)
 * | Frontend | ---a JsonRPC cal--> | Backend |
 * - the message is conveyed by JSON, so the arg is a string
 * - we return the result as string as well, a JSON
 */
void increment(const char* id, const char* req, void* arg)
{
    context_t* context = (context_t*)arg;
    context->count += 1;
    char result[4] = {0};
    (void)sprintf(result, "%ld", context->count);
    webview_return(context->w, id, 0, result);
}

/*
 * noob approach to navigate to another view
 */
void link(const char* id, const char* req, void* arg)
{
    const context_t* ctx = (context_t*) arg;
    // by setting the page without resolving current promise, resources myt leak, idk 4 sure.
    webview_set_html(ctx->w, second);
    webview_return(ctx->w, id, 0, "");
}

int main()
{
    const webview_t window = webview_create((int)DEBUG, NULL); // NOLINT(*-misplaced-const)

    webview_set_title(window, "cauri-test");
    webview_set_size(window, 640, 480, WEBVIEW_HINT_NONE);

    // context for binding
    static long _count = 0;
    context_t context = {.w = window, .count = _count};

    // bind methods
    webview_bind(window, "incr", increment, &context);
    webview_bind(window, "next", link, &context);

    // init window with homepage
    webview_set_html(window, home);
    webview_run(window);

    // clean up & exit
    webview_destroy(window);
    exit(EXIT_SUCCESS);
}
