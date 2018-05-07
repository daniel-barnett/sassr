# sassr
[![Build Status](https://travis-ci.org/daniel-barnett/sassr.svg?branch=master)](https://travis-ci.org/daniel-barnett/sassr)
[![Build status](https://ci.appveyor.com/api/projects/status/qqhn4cq77egjgg9p/branch/master?svg=true)](https://ci.appveyor.com/project/daniel-barnett/sassr/branch/master)

Sass Compiler for R: R bindings to [libsass](https://github.com/sass/libsass). 

## Installation

sassr is currently only available through GitHub. sassr compiles libsass during the installation process so no external dependencies are required on any platform aside from the usual requirements for compiling C/C++ (e.g. Rtools on Windows platforms). 

```{r}
# install.packages("devtools")
devtools::install_github("daniel-barnett/sassr")
```
## Purpose

[Sass (Syntactically Awesome StyleSheets)](https://sass-lang.com/) is a powerful stylesheet preprocessor that compiles to standard CSS and provides features missing in regular CSS such as variables, inheritance, mix-ins, and functions. As Sass compiles into standard CSS, using Sass will not affect the compatibility of your stylesheets for end users --- it simply makes certain tasks easier for the developer. sassr makes it easy to use the power of Sass in R and Shiny without the need for downloading or running external tools each time you run a Shiny server. To learn Sass, please use the official [Sass Basics guide](https://sass-lang.com/guide).

## Usage

sassr can deal with both Sass files and strings containing Sass code. 

### Sass character strings

```{r}
library(sassr)

# Compiling a simple string
sass_compile_string("foo { margin: 5px * 4; }")
#> [1] "foo {\n  margin: 20px; }\n"

# sassr can compile character vectors of any length
sass_compile_string(c(
  "foo { margin: 5px * 4; }",
  "$bg-col:  blue; bar { background-color: $bg-col; }",
  "baz { color: lighten(#ff0000, 30%); }"
))
#> [1] "foo {\n  margin: 20px; }\n"          
#> [2] "bar {\n  background-color: blue; }\n"
#> [3] "baz {\n  color: #ff9999; }\n"  
```

### Sass files

```{r}
# Simply pass the Sass filename in and sassr will return the compiled CSS in R form.
sass_string <- c(
  "foo { margin: 5px * 4; }",
  "$bg-col:  blue; bar { background-color: $bg-col; }",
  "baz { color: lighten(#ff0000, 30%); }"
)

temp_file <- tempfile(fileext = ".scss")
writeLines(sass_string, temp_file)

sass_compile_file(temp_file)
#> [1] "foo {\n  margin: 20px; }\n\nbar {\n  background-color: blue; }\n\nbaz {\n  color: #ff9999; }\n"

# sassr can also compile "indented syntax" Sass files with the "sass" extension.
sass_string_indent <- c(
  "foo \n  margin: 5px * 4\n",
  "$bg-col: blue \nbar \n  background-color: $bg-col \n",
  "baz \n  color: lighten(#ff0000, 30%) \n"
)

cat(sass_string_indent, sep = "\n")
#> foo 
#>   margin: 5px * 4
#> 
#> $bg-col: blue 
#> bar 
#>   background-color: $bg-col 
#> 
#> baz 
#>   color: lighten(#ff0000, 30%) 

temp_file <- tempfile(fileext = ".sass")
writeLines(sass_string_indent, temp_file)

sass_compile_file(temp_file)
#> [1] "foo {\n  margin: 20px; }\n\nbar {\n  background-color: blue; }\n\nbaz {\n  color: #ff9999; }\n"
```

### Output options

sassr supports most options provided by the libsass library, including output styles and formatting, output CSS commenting and precision of computed numeric values. A full list is provided by `?sassr`.

```{r}
# The "compressed" output style is useful for production as it minifies your CSS
sass_compile_string("foo { margin: 5px * 4; }", options = list(output_style = "compressed"))
#> [1] "foo{margin:20px}\n"

# Other output styles:
cat(sass_compile_string("foo { margin: 5px * 4; }", options = list(output_style = "nested")))
#> foo {
#>   margin: 20px; }

cat(sass_compile_string("foo { margin: 5px * 4; }", options = list(output_style = "expanded")))
#> foo {
#>   margin: 20px;
#> }

cat(sass_compile_string("foo { margin: 5px * 4; }", options = list(output_style = "compact")))
#> foo { margin: 20px; }

# Precision:
sass_compile_string("foo { margin: 2.718px * 3.141; }")
#> [1] "foo {\n  margin: 8.53724px; }\n"

sass_compile_string("foo { margin: 2.718px * 3.141; }", options = list(precision = 2))
#> [1] "foo {\n  margin: 8.54px; }\n"

# Indent character:
sass_compile_string("foo { margin: 5px * 4; }", options = list(indent = '\t'))
#> [1] "foo {\n\tmargin: 20px; }\n"
```

### Shiny integration

sassr integrates seamlessly into a Shiny workflow by providing the `shiny_sass()` function. This function takes the output of either `sass_compile_file()` or `sass_compile_string()` and inserts the compiled CSS into the HTML header. 

```{r}
# in a ui.R file:
# shiny_sass(sass_compile_file("styles.scss"))
# (not pushed yet - but the following works right now)

# the following is equivalent as sassr simply returns compiled CSS strings
# tags$head(
#   tags$style(
#     sass_compile_file("styles.scss")
#   )
# )
```
