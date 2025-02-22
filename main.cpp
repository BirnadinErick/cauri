#include "webview/webview.h"
#include <iostream>

int main() {
    try {
        webview::webview w(false, nullptr);
        w.set_title("Basic example");
        w.set_size(480, 320, WEBVIEW_HINT_NONE);
        w.set_html("Thanks for using webview!");
        w.run();
    } catch (const webview::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}