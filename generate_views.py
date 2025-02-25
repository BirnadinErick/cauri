import os


def get_formatted_filenames(dir: str) -> dict:
    """
    Reads files in the given directory and returns a dictionary
    where keys are file names (uppercase, dashes replaced with underscores)
    without extensions and values are the original filenames.
    """
    formatted_files = {}

    for file in os.listdir(dir):
        filepath, content = os.path.join(dir, file), ''
        if not (os.path.isfile(filepath)):
            continue

        name, _ = os.path.splitext(file)
        formatted_name = name.upper().replace('-', '_')
        with open(filepath, 'r') as f:
            content = f.read()
        formatted_files[formatted_name] = content

    return formatted_files


template = """
#include <string.h>

const char* FILE = R"html( <content> )html";

const char* get_view_html(const char* route) {
    if (strncmp(route, FILE, <strlen of FILE>) == 0) { return FILE;}
    
    return "Page not found";
}
"""

if __name__ == "__main__":
    directory = "views"
    generated_file_name = "views.c"
    if os.path.isdir(directory):
        views = get_formatted_filenames(directory)
        view_impls = [f"const char* {name}= R\"html( {content} )html\";" for name, content in views.items()]
        view_router = [
            "if (strncmp(route, " + file + ", " + str(len(file)) + ") == 0) { return " + file + ";}"
            for file in views.keys()
        ]

        # construct the file
        file_template = "#include <string.h>\n\n"
        file_template += "\n\n".join(view_impls)
        file_template += "\n\nconst char* get_view_html(const char* route) {\n"
        file_template += "\n".join(view_router)
        file_template += "\nreturn \"Page not found\";\n}"

        # write the file
        if not (os.path.isfile(generated_file_name)):
            with open('views.c', 'x') as f:
                f.write(file_template)
        else:
            with open('views.c', 'w') as f:
                f.write(file_template)


    else:
        print("`views` dir not found!")
