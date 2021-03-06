# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#' Compile Sass file into CSS
#'
#' This function compiles a file containing Sass code.
#'
#' @param filename A Sass file (.scss, .sass)
#' @param options A list containing options for libsass
#' @export
sass_compile_file <- function(filename, options = NULL) {
    .Call('_sassr_sass_compile_file', PACKAGE = 'sassr', filename, options)
}

#' Compile Character Vector to CSS
#'
#' This function compiles character vectors containing Sass code.
#'
#' @param strings A character vector of Sass
#' @param options A list containing options for libsass
#' @export
sass_compile_string <- function(strings, options = NULL) {
    .Call('_sassr_sass_compile_string', PACKAGE = 'sassr', strings, options)
}

