#' sassr: A Sass Compiler for R
#'
#' @section Compiler Options:
#'
#' The compiler functions in sassr understand the following options passed as a list:
#' \itemize{
#' \item precision A integer that determines the precision of fractional numbers.
#' \item output_style A..... For examples: \url{http://www.sass-lang.com/documentation/file.SASS_REFERENCE.html#output_style}
#' \item source_comments Emit comments in the generated CSS indicating the corresponding source line.
#' \item source_map_embed Embed sourceMappingUrl as data uri
#' \item is_indented_syntax_src Treat source string or file as sass (instead of scss). See \url{}.
#' \item indent A string to be used for indentation
#' \item linefeed A string to be used for line feeds (newlines)
#' }
#'
#' @docType package
#' @author Daniel Barnett <dbar344@aucklanduni.ac.nz>
#' @import Rcpp
#' @importFrom Rcpp evalCpp
#' @useDynLib sassr
#' @name sassr
NULL
