<?php
/**
 * @file
 * Helper functions for writing DCAT.
 */

define('SDCATE_RDF', 'http://www.w3.org/1999/02/22-rdf-syntax-ns#');
define('SDCATE_RDF_TYPE', SDCATE_RDF . 'type');

define('SDCATE_XSD', 'http://www.w3.org/2001/XMLSchema#');
define('SDCATE_XSD_DTIME', SDCATE_XSD . 'dateTime');
define('SDCATE_XSD_DEC', SDCATE_XSD . 'decimal');

define('SDCATE_DCAT', 'http://www.w3.org/ns/dcat#');
define('SDCATE_DCAT_ACAT', SDCATE_DCAT . 'Catalog');
define('SDCATE_DCAT_ADSET', SDCATE_DCAT . 'Dataset');
define('SDCATE_DCAT_ADIST', SDCATE_DCAT . 'Distribution');
define('SDCATE_DCAT_DSET', SDCATE_DCAT . 'dataset');
define('SDCATE_DCAT_DIST', SDCATE_DCAT . 'distribution');

define('SDCATE_DCAT_CONTACT', SDCATE_DCAT . 'contactPoint');
define('SDCATE_DCAT_PAGE', SDCATE_DCAT . 'landingPage');
define('SDCATE_DCAT_TAG', SDCATE_DCAT . 'keyword');
define('SDCATE_DCAT_THEME', SDCATE_DCAT . 'theme');
define('SDCATE_DCAT_URL', SDCATE_DCAT . 'downloadURL');
define('SDCATE_DCAT_SIZE', SDCATE_DCAT . 'byteSize');
define('SDCATE_DCAT_TYPE', SDCATE_DCAT . 'mediaType');

define('SDCATE_DT', 'http://purl.org/dc/terms/');
define('SDCATE_DT_CREAT', SDCATE_DT . 'issued');
define('SDCATE_DT_DESC', SDCATE_DT . 'description');
define('SDCATE_DT_GEO', SDCATE_DT . 'spatial');
define('SDCATE_DT_LANG', SDCATE_DT . 'language');
define('SDCATE_DT_MODIF', SDCATE_DT . 'modified');
define('SDCATE_DT_TITLE', SDCATE_DT . 'title');
define('SDCATE_DT_FORMAT', SDCATE_DT. 'format');
define('SDCATE_DT_PUBLISHER', SDCATE_DT. 'publisher');

define('SDCATE_FOAF', 'http://xmlns.com/foaf/0.1/');
define('SDCATE_FOAF_DOC', SDCATE_FOAF . 'Document');
define('SDCATE_FOAF_HOME', SDCATE_FOAF . 'homepage');


/**
 * Creates RDF triple.
 *
 * @param string $subject
 *   Subject of this triple as URI.
 * @param string $predicate
 *   Predicate of this triple as URI.
 * @param string $object
 *   Object of this triple as URI.
 *
 * @return string
 *   String representation of the triple.
 */
function sdcate_triple($subject, $predicate, $object) {
  return "<$subject> <$predicate> <$object> . \n";
}

/**
 * Create RDF triple.
 *
 * @param string $subject
 *   Subject of this triple as URI.
 * @param string $predicate
 *   Predicate of this triple as URI.
 * @param string $literal
 *   String to be added as object.
 * @param string $lang
 *   Optional language identifier.
 *
 * @return string
 *   String representation of the triple.
 */
function sdcate_literal($subject, $predicate, $literal, $lang = '') {
  $object = '"' . addcslashes($literal, "\\\'\"\n\r") . '"';
  if (isset($lang) && !empty($lang)) {
    $object .= '@' . $lang;
  }
  return "<$subject> <$predicate> $object .\n";
}

/**
 * Create RDF triple.
 *
 * @param string $subject
 *   Subject of this triple as URI.
 * @param string $predicate
 *   Predicate of this triple as URI.
 * @param string $stamp
 *   Timestamp (in seconds since epoch).
 *
 * @return string
 *   String representation of the triple.
 */
function sdcate_date($subject, $predicate, $stamp) {
  $object = '"' . date(DATE_ISO8601, $stamp) . '"';
  $object .= '^^<' . SDCATE_XSD_DTIME . '>';
  return "<$subject> <$predicate> $object .\n";
}

/**
 * Create RDF triple.
 *
 * @param string $subject
 *   Subject of this triple as URI.
 * @param string $predicate
 *   Predicate of this triple as URI.
 * @param string $decimal
 *   Decimal as string.
 *
 * @return string
 *   String representation of the triple.
 */
function sdcate_decimal($subject, $predicate, $decimal) {
  $object = '"' . $decimal . '"';
  $object .= '^^<' . SDCATE_XSD_DEC . '>';
  return "<$subject> <$predicate> $object .\n";
}
