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
To use this module, you will have first to install the Variable module.
Cron must be enabled.
This module was developed for the Drupal 7.

#INSTALLATION
How do we install a module in Drupal ?
First, you have to download the module and extract it in your folder
sites/all/modules
Secondly, you have to go to the Module page at Administrater>Modules and enable all the modules needed.
See https://drupal.org/documentation/install/modules-themes/modules-7
for further information.


#CONFIGURATION
Configure user permissions in Admin >> People >> Permissions:
- Administer DCAT

Customize the settings in Admin >> Configuration >> Search and Metadata
- Simple DCAT export:
 

