<?php

/*
 +-----------------------------------------------------------------------+
 | program/steps/mail/getunread.inc                                      |
 |                                                                       |
 | This file is part of the Roundcube Webmail client                     |
 | Copyright (C) 2005-2009, Roundcube Dev. - Switzerland                 |
 | Licensed under the GNU GPL                                            |
 |                                                                       |
 | PURPOSE:                                                              |
 |   Check all mailboxes for unread messages and update GUI              |
 |                                                                       |
 +-----------------------------------------------------------------------+
 | Author: Thomas Bruederli <roundcube@gmail.com>                        |
 +-----------------------------------------------------------------------+

 $Id: getunread.inc 4294 2010-12-01 09:52:23Z alec $

*/

$a_folders = $IMAP->list_mailboxes();

if (!empty($a_folders))
{
  $current = $IMAP->get_mailbox_name();
  $inbox = ($current == 'INBOX');
  $check_all = (bool)$RCMAIL->config->get('check_all_folders');

  foreach ($a_folders as $mbox_row) {
    $unseen_old = rcmail_get_unseen_count($mbox_row);

    if (!$check_all && $unseen_old !== null && $mbox_row != $current)
      $unseen = $unseen_old;
    else
      $unseen = $IMAP->messagecount($mbox_row, 'UNSEEN', $unseen_old === null);

    if ($unseen || $unseen_old === null) {
      $OUTPUT->command('set_unread_count', $mbox_row, $unseen, $inbox && $mbox_row == 'INBOX');
    }

    rcmail_set_unseen_count($mbox_row, $unseen);
  }
}

$OUTPUT->send();


