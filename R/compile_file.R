sass_compile <- function(string, file, options = NULL) {
  if (all(missing(string), missing(file))) {
    stop("A `string` or `file` must be passed to sass_compile()")
  } else if (all(!missing(string), !missing(file))) {
    stop("Only one of `string` or `file` must be passed to sass_compile()")
  }

  if (!missing(string)) {
    ## sass_compile_string(string, options)
  } else if (!missing(file)) {
    sass_compile_file(options)
  }
}
