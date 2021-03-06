<?php

if (!defined("LIMITED_FIELDS")) {
  define("LIMITED_FIELDS", "id, person, added, hours, start, end, details");
}

$notifier_email = $GLOBAL_AUTH_USERNAME;
$data = ldap_find($connection, "mail=". $notifier_email, array("manager", "cn"));
$notifier_name = $data[0]["cn"][0];

$manager_dn = $data[0]["manager"][0];
// "OMG, not querying LDAP for the real email? That's cheating!"
preg_match("/mail=([a-z]+@mozilla.*),o=/", $manager_dn, $matches);
$manager_email = $matches[1];
$is_hr = in_array($manager_email, $hr_managers);
// Exclude details from non-HR personnel
$fields = $is_hr ? '*' : LIMITED_FIELDS;

