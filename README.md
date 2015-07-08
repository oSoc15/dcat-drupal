# dcat-drupal
A drupal module to add and manage meta-data about datasets based on DCAT.

#INTRODUCTION
The Simple DCAT export module generates a file containing metadata (title,
link, description ...) of downloadable, machine-readable files.
This makes it easier for Drupal site owners to provide input for open data
initiatives / portals.

For more information about the metadata format, see:
- W3C's Data Catalog Vocabulary (http://www.w3.org/TR/vocab-dcat/)
- the European DCAT-AP project 
(https://joinup.ec.europa.eu/asset/dcat_application_profile/description)


#REQUIREMENTS
This module requires the Variable module.
Cron must be enabled.

#INSTALLATION
Install as you would normally install a contributed Drupal module.
See https://drupal.org/documentation/install/modules-themes/modules-7
for further information.


#CONFIGURATION
Configure user permissions in Admin >> People >> Permissions:
- Administer DCAT

Customize the settings in Admin >> Configuration >> Search and Metadata
>> Simple DCAT export:
 

