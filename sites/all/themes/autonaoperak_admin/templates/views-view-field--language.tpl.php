<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
$language = '';
if(isset($row->node_language)) {
  $language = $row->node_language;
}elseif(isset($row->taxonomy_term_data_language)) {
  $language = $row->taxonomy_term_data_language;
}

if($language == 'cs') {
  print '<span class="language-icon-cs">' . $output . '</span>';
}elseif($language == 'en') {
  print '<span class="language-icon-en">' . $output . '</span>';
}elseif($language == 'sk') {
  print '<span class="language-icon-sk">' . $output . '</span>';
}else {
  print $output;
}
