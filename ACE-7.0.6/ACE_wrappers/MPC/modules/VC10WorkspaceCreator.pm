package VC10WorkspaceCreator;

# ************************************************************
# Description   : A VC10 Workspace Creator
# Author        : Johnny Willemsen
# Create Date   : 11/10/2008
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;

use VC10ProjectCreator;
use VC9WorkspaceCreator;

use vars qw(@ISA);
@ISA = qw(VC9WorkspaceCreator);

# ************************************************************
# Subroutine Section
# ************************************************************

sub pre_workspace {
  my($self, $fh) = @_;
  my $crlf = $self->crlf();

  print $fh '﻿', $crlf,
            'Microsoft Visual Studio Solution File, Format Version 11.00', $crlf;
  $self->print_workspace_comment($fh,
            '# Visual Studio 2010', $crlf,
            '#', $crlf,
            '# This file was generated by MPC.  Any changes made directly to', $crlf,
            '# this file will be lost the next time it is generated.', $crlf,
            '#', $crlf,
            '# MPC Command:', $crlf,
            '# ', $self->create_command_line_string($0, @ARGV), $crlf);
}

sub website_extra_props {
  my($self, $fh) = @_;
  print $fh "\t\t" .
      'TargetFrameworkMoniker = ".NETFramework,Version%3Dv4.0"' .
      $self->crlf();
}

sub cpp_proj_ref {
  my($self, $spc, $refguid, $attr, $relative) = @_;
  my $crlf = $self->crlf();
  return $spc . '<ProjectReference Include="' . $relative . '">' . $crlf .
      $spc . "\t<Project>\{$refguid\}</Project>$crlf" .
      (defined $$attr{'copylocal'}
       ? $spc . "\t<Private>" . $$attr{'copylocal'} . "</Private>$crlf"
       : ''
      ) .
      $spc . '</ProjectReference>' . $crlf;
}

1;
