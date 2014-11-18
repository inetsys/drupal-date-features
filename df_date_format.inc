<?php
function df_date_format_load($format=null){
	$roles = user_roles();
	$query = db_select('date_formats','df')
		->fields('df', array('format', 'type', 'locked'))
		->condition('type', 'custom', '=');
	if($format){
		$query->condition('format', $format, '=');
	}
	$query->orderBy('dfid', 'asc');
	$result = $query->execute();
	$list = array();
	foreach($result as $record){
		$list[] = $record;
	}

	return $format && count($list) == 1 ? $list[0] : $list;
}

function df_date_format_delete($df_date_format){
	$df_date_format = (object) $df_date_format;

	db_delete('date_formats')
		->condition('format', $df_date_format->format)
		->execute();
}

function df_date_format_save($df_date_format){
	$df_date_format = (object) $df_date_format;
	df_date_format_delete($df_date_format);
	db_insert('date_formats')
		->fields(array(
			'format' => $df_date_format->format,
			'type' => 'custom',
			'locked' => 0,
		))
		->execute();
}