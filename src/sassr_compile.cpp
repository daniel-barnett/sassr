#include <Rcpp.h>
#include <stdio.h>
#include <sass.h>

using namespace Rcpp;

int set_options(Sass_Options* ctx_opt, List opt_list) {
  if (opt_list.containsElementNamed("precision")) {
    sass_option_set_precision(ctx_opt, as<int>(opt_list["precision"]));
  }

  if (opt_list.containsElementNamed("output_style")) {
    sass_option_set_output_style(ctx_opt, static_cast<Sass_Output_Style>(as<int>(opt_list["output_style"])));
  }

  if (opt_list.containsElementNamed("source_comments")) {
    sass_option_set_source_comments(ctx_opt, as<bool>(opt_list["source_comments"]));
  }

  if (opt_list.containsElementNamed("source_map_embed")) {
    sass_option_set_source_map_embed(ctx_opt, as<bool>(opt_list["source_map_embed"]));
  }

  if (opt_list.containsElementNamed("source_map_contents")) {
    sass_option_set_source_map_contents(ctx_opt, as<bool>(opt_list["source_map_contents"]));
  }

  if (opt_list.containsElementNamed("source_map_file_urls")) {
    sass_option_set_source_map_file_urls(ctx_opt, as<bool>(opt_list["source_map_file_urls"]));
  }

  if (opt_list.containsElementNamed("omit_source_map_url")) {
    sass_option_set_omit_source_map_url(ctx_opt, as<bool>(opt_list["omit_source_map_url"]));
  }

  if (opt_list.containsElementNamed("is_indented_syntax_src")) {
    sass_option_set_is_indented_syntax_src(ctx_opt, as<bool>(opt_list["is_indented_syntax_src"]));
  }

  if (opt_list.containsElementNamed("indent")) {
    sass_option_set_indent(ctx_opt, as<const char*>(opt_list["indent"]));
  }

  if (opt_list.containsElementNamed("linefeed")) {
    sass_option_set_linefeed(ctx_opt, as<const char*>(opt_list["linefeed"]));
  }

  return 0;
}

// [[Rcpp::export]]
NumericVector sass_compile_file(const char* filename, List options = R_NilValue) {
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

// [[Rcpp::export]]
CharacterVector sass_compile_string(std::vector<std::string> strings, List options = R_NilValue) {
  CharacterVector compiled_strings(strings.size());

  for (int i = 0; i < strings.size(); i++) {
    char* curr_string = strdup(strings[i].c_str());

    struct Sass_Data_Context* data_ctx = sass_make_data_context(curr_string);
    struct Sass_Context* ctx = sass_data_context_get_context(data_ctx);
    struct Sass_Options* ctx_opt = sass_context_get_options(ctx);

    if (!options.isNULL()) {
      set_options(ctx_opt, options);
    }

    int status = sass_compile_data_context(data_ctx);

    if (status > 0) {
      std::string error_msg = sass_context_get_error_message(ctx);
      sass_delete_data_context(data_ctx);
      stop(error_msg);
    }

    compiled_strings(i) = sass_context_get_output_string(ctx);

    sass_delete_data_context(data_ctx);
  }

  return compiled_strings;
}
