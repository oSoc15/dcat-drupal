<?php
/**
 * @file
 * Variable API module. Definition for variables.
 */

/**
 * Get deafult DCAT Catalog URI.
 *
 * @return string
 *   Default URI
 */
function sdcate_default_uri() {
  global $base_url;

  $uri = str_replace('https', 'http', $base_url);
  $uri = str_replace('http://', 'http://dcat.', $base_url);
  return $uri;
}

/**
 * Implements hook_variable_info().
 */
function sdcate_variable_info($options) {
  $variables['sdcate_outfile'] = array(
    'type' => 'string',
    'group' => 'sdcate',
    'title' => t('Output file'),
    'description' => t('Name of the DCAT export file.'),
    'localize' => FALSE,
    'default' => 'dcat.n3',
    'required' => 'TRUE',
  );
  $variables['sdcate_uri'] = array(
    'type' => 'uri',
    'group' => 'sdcate',
    'title' => t('Catalog URI'),
    'description' => t('Unique ID for the Catalog.'),
    'localize' => FALSE,
    'default callback' => 'sdcate_default_uri',
    'required' => TRUE,
  );
  $variables['sdcate_license'] = array(
    'type' => 'uri',
    'group' => 'sdcate',
    'title' => t('Default license'),
    'description' => t('Link to the default open license.'),
    'localize' => FALSE,
  );
  $variables['sdcate_files'] = array(
    'type' => 'string',
    'group' => 'sdcate',
    'title' => t('File extensions'),
    'description' => t('List of machine-friendly file formats.'),
    'localize' => FALSE,
    'default' => 'csv json kml kmz ods rdf txt xls xlsx xml',
    'required' => TRUE,
  );
  $variables['sdcate_theme'] = array(
    'type' => 'uri',
    'group' => 'sdcate',
    'title' => t('Category'),
    'description' => t('URI of a taxonomy term, e.g. http://eurovoc.europa.eu/637'),
    'localize' => FALSE,
  );
  $variables['sdcate_geo'] = array(
    'type' => 'uri',
    'group' => 'sdcate',
    'title' => t('Geographic coverage'),
    'description' => t('URI of geographic region, e.g. http://sws.geonames.org/2802361/'),
    'localize' => FALSE,
  );
  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function sdcate_variable_group_info() {
  $groups['sdcate'] = array(
    'title' => t('Simple DCAT settings'),
    'description' => t('Simple DCAT settings'),
    'access' => 'administer sdcate',
  );
  return $groups;
}


/**
 * Validate callback for URLs.
 *
 * @param array $form
 *   Form to validate.
 * @param array $form_state
 *   Form state.
 */
function sdcate_valid_uri(&$form, &$form_state) {
  if (isset($form['value']) && !empty($form['value'])) {
    if (!valid_url($form['value'], TRUE)) {
      form_set_error($form['name'], t('Invalid URI.'));
    }
  }
}

/**
 * Implements hook_variable_type_info().
 */
function sdcate_variable_type_info() {
  $types['uri'] = array(
    'type' => 'url',
    'title' => t('URI'),
    'validate callback' => 'sdcate_valid_uri',
  );
  return $types;
}
