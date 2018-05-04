#include <Rcpp.h>
#include <stdio.h>
#include <sass.h>

using namespace Rcpp;

int set_options(Sass_Options* ctx_opt, List opt_list) {
  if (opt_list.containsElementNamed("precision")) {
    sass_option_set_precision(ctx_opt, as<int>(opt_list["precision"]));
  }
  return 0;
}

// [[Rcpp::export]]
NumericVector sass_compile_file(CharacterVector filename_arg, List options = R_NilValue) {
  const char* filename = as<const char*>(filename_arg);

  struct Sass_File_Context* file_ctx = sass_make_file_context(filename);
  struct Sass_Context* ctx = sass_file_context_get_context(file_ctx);
  struct Sass_Options* ctx_opt = sass_context_get_options(ctx);

  if (!options.isNULL()) {
    set_options(ctx_opt, options);
  }

  int status = sass_compile_file_context(file_ctx);

  if (status == 0)
    puts(sass_context_get_output_string(ctx));
  else
    puts(sass_context_get_error_message(ctx));

  sass_delete_file_context(file_ctx);

  return NumericVector::create(0, 1);
}
