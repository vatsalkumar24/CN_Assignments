package VS2017WorkspaceCreator;

# ************************************************************
# Description   : A vs2017 (Visual Studio 2017) Workspace Creator
# Author        : Johnny Willemsen
# Create Date   : 01/05/2016
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;

use VS2017ProjectCreator;
use VC12WorkspaceCreator;

use vars qw(@ISA);
@ISA = qw(VC12WorkspaceCreator);

# ************************************************************
# Subroutine Section
# ************************************************************

sub pre_workspace {
  my($self, $fh) = @_;
  my $crlf = $self->crlf();

  print $fh '﻿', $crlf,
            'Microsoft Visual Studio Solution File, Format Version 12.00', $crlf;
  $self->print_workspace_comment($fh,
            '# Visual Studio 15', $crlf,
            '#', $crlf,
            '# This file was generated by MPC.  Any changes made directly to', $crlf,
            '# this file will be lost the next time it is generated.', $crlf,
            '#', $crlf,
            '# MPC Command:', $crlf,
            '# ', $self->create_command_line_string($0, @ARGV), $crlf);
}


1;
