<?php
/**
 * @file
 * Helper functions for scraping / scanning nodes.
 */

/**
 * Get the list of content types with a file field.
 *
 * @return array
 *   Array with node types and their file fields.
 */
function sdcate_filefields_list() {
  $nodes = array();

  $map = field_info_field_map();
  foreach ($map as $fieldname => $field) {
    if ($field['type'] == 'file') {
      if (isset($field['bundles']['node'])) {
        foreach ($field['bundles']['node'] as $nodename) {
          $nodes[$nodename][] = $fieldname;
        }
      }
    }
  }
  return $nodes;
}

/**
 * Get the list of (managed) files.
 *
 * @return array
 *   Array of file ids.
 */
function sdcate_files_list() {
  $files = array();

  $ends = variable_get_value('sdcate_files');
  foreach (explode(' ', $ends) as $end) {
    $query = new EntityFieldQuery();
    $res = $query->entityCondition('entity_type', 'file')
                 ->propertyCondition('uri', 'public://', 'STARTS_WITH')
                 ->propertyCondition('uri', '%.' . $end, 'LIKE')
                 ->execute();
    if (isset($res) && isset($res['file'])) {
      $files = array_merge($files, array_keys($res['file']));
    }
  }
  return $files;
}

/**
 * Get the list of nodes to scrape for files.
 *
 * @return array
 *   Array of node ids.
 */
function sdcate_nodes_list() {
  $types = sdcate_filefields_list();
  $ids = sdcate_files_list();

  $nids = array();
  foreach ($types as $name => $fields) {
    foreach ($fields as $field) {
      $query = new EntityFieldQuery();
      $res = $query->entityCondition('entity_type', 'node')
                   ->entityCondition('bundle', $name)
                   ->propertyCondition('status', NODE_PUBLISHED)
                   ->fieldCondition($field, 'fid', $ids)
                   ->execute();
      if (isset($res) && isset($res['node'])) {
        $nids = array_merge($nids, array_keys($res['node']));
      }
    }
  }
  return $nids;
}
