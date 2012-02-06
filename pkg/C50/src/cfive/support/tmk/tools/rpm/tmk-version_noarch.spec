#
# tmk rpm spec file : Copyright (C) 2004 Yamauchi Hitoshi
# $Id: tmk-version_noarch.spec,v 1.2 2004/09/13 17:54:12 yamauchih Exp $
#
Summary: a tcl based intelligent make tool. 
Name: tmk
Version: 0.91
Release: 0
Copyright: GPL
Group: Development/Tools
Source: tmk-0.91.tar.gz
URL: https://sourceforge.net/projects/tmk/
# Distribution: Linux
# Vendor: Hartmut Schirmacher, Stefan Brabec, and tmk users
Packager: Yamauchi Hitoshi <hitoshi_at_mpi-sb.mpg.de.delete.here>
Summary(ja): tcl �١����Υ���ƥꥸ����Ȥ� make.
Requires: tcl >= 8.0
Prefix: /opt
BuildArch: noarch

%description
tmk - a tcl based intelligent make tool. This make tool combines the
functionality of a traditional make utility with the power of the Tcl
scripting language. Make is a good tool for solving dependency
relationship, however, if you want to introduce some condition to the
dependency, it became a difficult problem, even it is possible. Then,
we combines make with tcl script --- tmk is a programmable make.
tmk works on everywhere where tcl runs.

%description -l ja
tmk - tcl �١����Υ���ƥꥸ����Ȥ� make �Ǥ�������� make �ϰ�¸�ط�
���褹�뤳�Ȥ���ܤ˺���Ƥ��ޤ������������Ǥ�����˽��äư�¸��
�����褹��褦�ʤ��Ȥϡ��Բ�ǽ�ǤϤʤ��ˤ����ʤ��ʤ��񤷤���Τ���
��ޤ��������ǡ�tmk �� make �� tcl �Υ�����ץȤ�Ϣư��������Ȥߤ�Ƴ
�����ޤ������Ĥޤꡤ�ץ�����ǽ�� make �Ǥ���tmk �� tcl ������ɤ�
�Ķ��Ǥ�ư�����Ȥ�ȯ���ʤ���Ƥ��ޤ���

# [rpm package] preparation before generate tmk-version.rpm.
%prep
rm -rfv ${RPM_BUILD_DIR}/opt

# [rpm package] expand source files to BUILD.
%setup

# [rpm package] Here is `make' process to build. 
%build
# nothing to do for build

# [rpm package] install procedure. 
%install
if [ ! -d ${RPM_BUILD_DIR}/opt/tmk ]; then
    mkdir -p ${RPM_BUILD_DIR}/opt/tmk
fi
if [ ! -d ${RPM_BUILD_DIR}/opt/tmk/bin ]; then
    mkdir -p ${RPM_BUILD_DIR}/opt/tmk/bin
fi
cp -rp tmk/* ${RPM_BUILD_DIR}/opt/tmk/
# Symlink has sometimes trouble (update, or erase and install), then copy it.
cp ${RPM_BUILD_DIR}/opt/tmk/src/tmk ${RPM_BUILD_DIR}/opt/tmk/bin/

# [rpm package] after generating rpm package.
%clean


# [rpm install] preprocessing of install.
%pre 


# [rpm install] postprocessing of install.
%post
if [ -f ${RPM_BUILD_DIR}/opt/tmk/bin/tmk ]; then
    rm ${RPM_BUILD_DIR}/opt/tmk/bin/tmk
fi
# Symlink has sometimes trouble (update, or erase and install), then copy it.
cp ${RPM_BUILD_DIR}/opt/tmk/src/tmk ${RPM_BUILD_DIR}/opt/tmk/bin/
chmod 755 ${RPM_BUILD_DIR}/opt/tmk/bin/tmk


# [rpm uninstall] postprocessing of uninstall.
%postun


# [file attributes]
%attr(755, root, root) ${RPM_BUILD_DIR}/opt/tmk/
%attr(755, root, root) ${RPM_BUILD_DIR}/opt/tmk/bin/tmk
%defattr(644, root, root)

# If the tmk is not really installed, binary package does not created.
# [files]
%files
/opt/tmk
#%config /opt/tmk/config/site/site-config.tmk

