<?php
/**
 * @file
 * Helper functions for writing DCAT.
 */

module_load_include('inc', 'sdcate', 'sdcate.rdf');
module_load_include('inc', 'sdcate', 'sdcate.scrape');

/**
 * Get the URI of the DCAT Catalog.
 *
 * @return string
 *   String respresentation of DCAT Catalog URI.
 */
function sdcate_uri_catalog() {
  $cat = &drupal_static(__FUNCTION__);
  if (!isset($cat)) {
    $cat = variable_get_value('sdcate_uri') . '/catalog';
  }
  return $cat;
}

/**
 * Get the URI of a DCAT Dataset.
 *
 * @param int $did
 *   Dataset ID, typically the node id.
 *
 * @return string
 *   String respresentation of DCAT dataset URI.
 */
function sdcate_uri_dataset($did) {
  return sdcate_uri_catalog() . '/dataset/' . $did;
}

/**
 * Get the URI of a DCAT Distribution.
 *
 * @param int $fid
 *   Distribution ID, typically the file id.
 *
 * @return string
 *   String respresentation of DCAT distribution URI.
 */
function sdcate_uri_distribution($fid) {
  return sdcate_uri_catalog() . '/distribution/' . $fid;
}


/**
 * Generate DCAT Catalog.
 *
 * @return string
 *   DCAT Catalog as RDF triples.
 */
function sdcate_catalog() {
  global $base_url;

  $cat = sdcate_uri_catalog();
  $triples = sdcate_triple($cat, SDCATE_RDF_TYPE, SDCATE_DCAT_ACAT);
  $triples .= sdcate_triple($cat, SDCATE_FOAF_HOME, $base_url);
  $triples .= sdcate_triple($cat, SDCATE_DT_PUBLISHER, $base_url );
  if ($geo = variable_get_value('sdcate_geo')) {
    $triples .= sdcate_triple($cat, SDCATE_DT_GEO, $geo);
  }
  if ($theme = variable_get_value('sdcate_theme')) {
    $triples .= sdcate_triple($cat, SDCATE_DCAT_THEME, $theme);
  }
  return $triples;
}

/**
 * Generate a DCAT Distribution.
 *
 * @param string $dset
 *   URI of the DCAT Dataset.
 * @param array $file
 *   File to be exported.
 *
 * @return string
 *   DCAT Distribution as RDF triples.
 */
function sdcate_distribution($dset, $file) {
  $dist = sdcate_uri_distribution($file['fid']);
  $url = file_create_url($file['uri']);

  $data = sdcate_triple($dset, SDCATE_DCAT_DIST, $dist);
  $data .= sdcate_triple($dist, SDCATE_RDF_TYPE, SDCATE_DCAT_ADIST);
  $data .= sdcate_literal($dist, SDCATE_DT_TITLE, $file['filename']);
  if (isset($file['description']) && !empty($file['description'])) {
    $data .= sdcate_literal($dist, SDCATE_DT_DESC, $file['description']);
  }
  $data .= sdcate_date($dist, SDCATE_DT_CREAT, $file['timestamp']);
  $data .= sdcate_decimal($dist, SDCATE_DCAT_SIZE, $file['filesize']);
  $data .= sdcate_literal($dist, SDCATE_DCAT_TYPE, $file['filemime']);
  $data .= sdcate_triple($dist, SDCATE_DCAT_URL, $url);

  return $data;
}

/**
 * Check if file is public and is a machine-friendly file format.
 *
 * @param array $file
 *   File to be checked.
 *
 * @return bool
 *   TRUE if a file is to public and n a open format.
 */
function sdcate_file_check($file) {
  $check = FALSE;

  // Check if file is public
  if ((substr($file['uri'], 0, 9) == 'public://') && ($file['display'] == 1)) { 
    // Check file extension
    if ($pos = strrpos($file['uri'], '.')) {
      $type = substr($file['uri'], $pos + 1);
      if ($type) {
        $types = explode(' ', variable_get_value('sdcate_files'));
        $check = in_array(strtolower($type), $types);
      }
    }
  }
  return $check;
}

/**
 * Generate DCAT Distributions.
 *
 * @param string $dset
 *   URI of the DCAT Dataset.
 * @param object $node
 *   Node to be exported.
 *
 * @return string
 *   DCAT Distributions as RDF triples.
 */
function sdcate_distributions($dset, $node) {
  $data = '';
  // Get the list of file fields.
  $fields = sdcate_filefields_list();
  foreach ($fields[$node->type] as $field) {
    if (isset($node->{$field}) && !empty($node->{$field})) {
      foreach (array_keys($node->{$field}) as $lang) {
        foreach ($node->{$field}[$lang] as $file) {
          if (sdcate_file_check($file)) {
            $data .= sdcate_distribution($dset, $file);
          }
        }
      }
    }
  }
  return $data;
}

/**
 * Generate a DCAT Dataset.
 *
 * @param string $cat
 *   URI of the DCAT Catalog.
 * @param object $node
 *   Node to be exported.
 *
 * @return as string
 *   DCAT Dataset as RDF triples.
 */
function sdcate_dataset($cat, $node) {
  global $language;
  $dset = sdcate_uri_dataset($node->nid);
  $keywords = '';
  $data = sdcate_triple($cat, SDCATE_DCAT_DSET, $dset);
  $data .= sdcate_triple($dset, SDCATE_RDF_TYPE, SDCATE_DCAT_ADSET);

  if($node->language == "und") { 
    $node->language = $language->language;
  }
  $data .= sdcate_literal($dset, SDCATE_DT_TITLE, $node->title, $node->language);
  /**
  * This following code is the keywords integration
  * 'field_file_tags' is the name of the field for the tags, he has to be change 
  * if the name change in the website.
  */
  $tags = field_get_items('node',$node,'field_file_tags');
  if(!empty($tags)){
    for( $i = 0; $i < sizeof( $tags ); $i++ ) {
      $tag_name = field_view_value('node', $node, 'field_file_tags', $tags[$i]);
      $keywords .= $tag_name['#title'];
      $data .= sdcate_literal($dset, SDCATE_DCAT_TAG, $tag_name['#title'], $node->language);
    }
  }
  

  $data .= sdcate_date($dset, SDCATE_DT_CREAT, $node->created);
  $data .= sdcate_date($dset, SDCATE_DT_MODIF, $node->changed);
  $data .= sdcate_distributions($dset, $node);  

  return $data;
}


/**
 * Generate DCAT Datasets.
 *
 * @return string
 *   DCAT Datasets as RDF triples.
 */
function sdcate_datasets() {
  $data = '';

  $cat = sdcate_uri_catalog();
  $nids = sdcate_nodes_list();
  foreach ($nids as $id) {
    $nodes = entity_load('node', array($id));
    if (isset($nodes) && !empty($nodes)) {
      $node = array_pop($nodes);
      // Check if anonymous user has access to this node.
      if (node_access('view', $node, 0)) {
        $data .= sdcate_dataset($cat, $node);
      }
    }
  }
  return $data;
}
