# sassr
Sass Compiler for R: R bindings to libsass. 

## Installation

sassr is currently only available through this GitHub repository.

```{r}
# install.packages("devtools")
devtools::install_github("daniel-barnett/sassr")
```
## Purpose

Sass (Syntactically Awesome StyleSheets) is a powerful stylesheet preprocessor that compiles to standard CSS. It provides features missing in regular CSS such as variables, inheritance, mix-ins, and even functions. As Sass compiles into standard CSS, using Sass will not affect the compatibility of your stylesheets --- it simply makes certain tasks easier. sassr makes it easy to use the power of Sass in R and Shiny as Sass files and strings can be compiled and included without any external tools.

## Usage

sassr can deal with both Sass files and strings containing Sass code. 

### Sass character strings

```{r}
library(sassr)

# Compiling a simple string
sass_compile_string("foo { margin: 5px * 4; }")

# sassr can compile character vectors of any length
sass_compile_string(c(
  "foo { margin: 5px * 4; }",
  "$bg-col:  blue; bar { background-color: $bg-col; }",
  "baz { color: lighten(#ff0000, 30%); }"
))
```

### Sass files

```{r}
# Simply pass the Sass filename in and sassr will return the compiled CSS in R form.
sass_compile_file("test.scss")

# sassr can also compile "indented syntax" Sass files
```

### Output options

sassr supports most options provided by the libsass library, including output styles and formatting, output CSS commenting and precision of computed numeric values. A full list is provided by `?sassr`.

```{r}

```

### Shiny integration

sassr integrates seamlessly into a Shiny workflow by providing the `shiny_sass()` function. This function takes the output of either `sass_compile_file()` or `sass_compile_string()` and inserts the compiled CSS into the HTML header. 

```{r}

```
