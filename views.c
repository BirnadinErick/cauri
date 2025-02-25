#include <string.h>

const char* HOME = R"html(
<p id="id">0</p>
<button id="btn">Incr</button>
<button id="link">Next</button>

<a href="second">Second</a>

<script>
    const id = document.querySelector("#id");
    const btn = document.querySelector("#btn");
    const anchors = document.querySelectorAll("a");

    btn.addEventListener("click", async function () {
        id.textContent = await window.incr();
    });

    for (let i = 0; i < anchors.length; i++) {
        anchors[i].addEventListener("click", async function (e) {
            e.preventDefault();
            let route = typeof (e.target.href) === 'string' ? e.target.href : '404';
            await window.route(route);
        })
    }

</script> )html";

const char* SECOND = R"html( <p>second page</p> )html";

const char* get_view_html(const char* route)
{
    if (strncmp(route, HOME, 4) == 0)
    {
        return HOME;
    }
    if (strncmp(route, SECOND, 6) == 0)
    {
        return SECOND;
    }
    return "Page not found";
}
