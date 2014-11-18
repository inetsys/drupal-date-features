<?php
function df_date_type_load($type=null){
	$roles = user_roles();
	$query = db_select('date_format_type','dft')
		->fields('dft')
		->condition('locked', 0, '=');
	if($type){
		$query->condition('type', $type, '=');
	}
	$query->orderBy('type', 'asc');
	$result = $query->execute();
	$list = array();
	foreach($result as $record){
		$list[] = $record;
	}

	return $type && count($list) == 1 ? $list[0] : $list;
}

function df_date_type_delete($df_date_type){
	$df_date_type = (object) $df_date_type;

	db_delete('date_format_type')
		->condition('type', $df_date_type->type)
		->execute();
}

function df_date_type_save($df_date_type){
	$df_date_type = (object) $df_date_type;
	df_date_type_delete($df_date_type);
	db_insert('date_format_type')
		->fields(array(
			'type' => $df_date_type->type,
			'title' => $df_date_type->title,
			'locked' => 0,
		))
		->execute();
}