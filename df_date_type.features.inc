<?php

function df_date_type_features_export($data, &$export, $module_name){
	$export['dependencies']['df_features'] = 'df_features';
	foreach ($data as $component) {
		$export['features']['df_date_type'][$component] = $component;
	}
	return array();
}

function df_date_type_features_export_options() {
	module_load_include('inc', 'df_features', 'df_date_type');

	$options = array();
	foreach(df_date_type_load() as $component) {
		$options[$component->type] = $component->title;
	}
	return $options;
}

function df_date_type_features_export_render($module_name, $data, $export = NULL) {
	module_load_include('inc', 'df_features', 'df_date_type');

	$code = array();
	$code[] = '$df_date_type = array();';
	foreach ($data as $type) {
		$code[] = "  \$df_date_type['{$type}'] = " . features_var_export(df_date_type_load($type)) .";";
	}
	$code[] = "return \$df_date_type;";
	$code = implode("\n", $code);
	return array('df_date_type_defaults' => $code);
}

function df_date_type_features_revert($module_name) {
	df_date_type_features_rebuild($module_name);
}

function df_date_type_features_rebuild($module_name) {
	module_load_include('inc', 'df_features', 'df_date_type');

	$df_date_types = module_invoke($module_name, 'df_date_type_defaults');
	if (!empty($df_date_types)) {
		foreach ($df_date_types as $df_date_type) {
			df_date_type_save($df_date_type);
		}
	}
}