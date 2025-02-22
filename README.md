# CAURI: documentation

**CAURI** is a Tauri-inspired but using C language. Why? Because.

this is just a tracking of what I learned about the workings of cauri.
this is to serve as a future reference. the documentation is not necessarily
technical and accurate. the descriptions explain what I perceive.

## TODO

- [x] window creation
- [x] load a view
- [x] communicate with backend
- [ ] navigate to another view
- [ ] navigate back
- [ ] create view workflow
- [ ] preserve view state during navigation
- [ ] how-to bootstrap a new project
- [ ] other-platform setup 

---

## Skeleton

```c
int main(void) {
    const webview_t window = webview_create((int)DEBUG, NULL);

    webview_set_title(window, "cauri-test");
    webview_set_size(window, 640, 480, WEBVIEW_HINT_NONE);

    webview_set_html(window, home);
    webview_run(window);

    webview_destroy(window);
    exit(EXIT_SUCCESS);
}
```

#### window handle creation

`webview_create` creates a webview window. takes 2 arguments. 

1. DEBUG: whether to allow debugging capabilities in the frontend
2. NULL: a window handle to embed the view.

> DEBUG: only works if the underlying view engine (e.g. GTK, WebView2 etc.) 
> supports *Inspect Element* functionality

#### decorating the window

following functions decorates the native window:

- webview_set_title: sets the title of the native window bar
- webview_set_size: sets the initial window size, user can resize the window

#### window content

`webview_set_html` sets the content inside to the *window*

#### initialize & bookkeeping

`webview_run` & `webview_destroy` are bookkeeping functions. there is nothing
more to say here.

---

## Communicating with backend

though webview allows 2-way communication, for now I am only focusing
on 1-way (i.e. Frontend -> Backend).

apart from skeleton, we need 3 things:

1. callback: a function to call; this will do the intended work
2. bind: let frontend know this callback exists
3. callback_arg: an argument struct that we need to give to the callback

### callback_arg

at least, we need to pass in the current webview window handle.

```c
typedef struct {
    webview_t window;
    // other stuff we need
} context_t;
```

### bind

we use the `webview_bind` method which takes 4 arguments in order:

1. w: the window handle
2. name: a name of the command to expose to the frontend
3. callback: the callback (as a function pointer)
4. arg: reference to the argument of the callback

```c
// context for binding
static long _count = 0;
context_t context = {.w = window, .count = _count};

// bind methods
webview_bind(window, "incr", increment, &context);
```

> the `name` will be what we would call in the frontend. (e.g. `window.incr()`).
> the bound method will be available in global *window* object in javascript

### callback

a function that we want to be called from the frontend. a *callback* takes 3
arguments:

1. id: an id of the request (to differentiate from multiple requests)
2. req: a JSON string that was passed from the frontend
3. arg: arg we passed during the binding (here, `context_t context`)

```c 
void increment(const char* id, const char* req, void* arg)
{
    context_t* context = (context_t*)arg;
    
    context->count += 1;
    char result[4] = {0};
    (void)sprintf(result, "%ld", context->count);
    
    webview_return(context->w, id, 0, result);
}
```

to let the frontend know of the result, we use `webview_return` as
`webview_return(context->w, id, 0, result)` (documentation WIP).

>[info] the *callback* can be also multithreaded. (documentation WIP);


## License: MIT License

Copyright (c) 2025 Birnadin Erick

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 ---

## Tschau

I hope this helps you in any way. if you have a comment, open an issue
and let me know, no matter how harsh it is.

Made in Deggendorf with 🥨 and 🍺;

Till then, it is methebe, signing off.
Tschau!

