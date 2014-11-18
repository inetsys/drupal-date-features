<?php

function df_date_format_features_export($data, &$export, $module_name){
	$export['dependencies']['df_features'] = 'df_features';
	foreach ($data as $component) {
		$export['features']['df_date_format'][$component] = $component;
	}
	return array();
}

function df_date_format_features_export_options() {
	module_load_include('inc', 'df_features', 'df_date_format');

	$options = array();
	foreach(df_date_format_load() as $component) {
		$options[$component->format] = date($component->format);
	}
	return $options;
}

function df_date_format_features_export_render($module_name, $data, $export = NULL) {
	module_load_include('inc', 'df_features', 'df_date_format');

	$code = array();
	$code[] = '$df_date_format = array();';
	foreach ($data as $format) {
		$code[] = "  \$df_date_format['{$format}'] = " . features_var_export(df_date_format_load($format)) .";";
	}
	$code[] = "return \$df_date_format;";
	$code = implode("\n", $code);
	return array('df_date_format_defaults' => $code);
}

function df_date_format_features_revert($module_name) {
	df_date_format_features_rebuild($module_name);
}

function df_date_format_features_rebuild($module_name) {
	module_load_include('inc', 'df_features', 'df_date_format');

	$df_date_formats = module_invoke($module_name, 'df_date_format_defaults');
	if (!empty($df_date_formats)) {
		foreach ($df_date_formats as $df_date_format) {
			df_date_format_save($df_date_format);
		}
	}
}