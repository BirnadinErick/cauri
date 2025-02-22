#include <iostream>
#include <string>

#include "views.h"
#include "webview/webview.h"


int main()
{
    // get homepage contents
    const auto home_page = home;

    try
    {
        int16_t count = 0;

        webview::webview w(false, nullptr);
        w.set_title("cauri");
        w.set_size(1280, 720, WEBVIEW_HINT_NONE);
        w.set_html(home_page);

        w.bind("incr", [&](const std::string& req) -> std::string { return std::to_string(++count); });
        w.run();
    }
    catch (const webview::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
