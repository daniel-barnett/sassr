#' Compile Sass strings or files
#'
#' @param string Character vector of Sass strings to compile
#' @param file Filename of a Sass file
#' @param options A list of output options.
#'
#' @return A character vector of CSS.
#' @export
#'
#' @seealso sass_compile_file sass_compile_string
#'
#' @examples
#' sass_string <- "foo { margin: 10px * 2.5; }"
#' sass_compile(string = sass_string)
#'
#' sass_string <- c(
#'   sass_string,
#'   "$bg-col:  blue; bar { background-color: $bg-col; }",
#'   "baz { color: lighten(#ff0000, 30%); }"
#' )
#' sass_compile(string = sass_string)
#'
#' test_file <- tempfile(fileext = "scss")
#' writeLines(sass_string, test_file)
#' sass_compile(file = test_file)
sass_compile <- function(string, file, options = NULL) {
  if (all(missing(string), missing(file))) {
    stop("A `string` or `file` must be passed to sass_compile()")
  } else if (all(!missing(string), !missing(file))) {
    stop("Only one of `string` or `file` must be passed to sass_compile()")
  }

  if (!missing(string)) {
    sass_compile_string(string, options)
  } else if (!missing(file)) {
    sass_compile_file(file, options)
  }
}
