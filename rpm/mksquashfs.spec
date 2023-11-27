%define name mksquashfs
%define version 2.2r2
%define rel 1
%define release b%{rel}

%define kernel_rel	%(eval uname -r)

Name:		%{name}
Summary:	The Compressed Loopback Block Device
Version:	%{version}
Release:	%{release}
License:	GPL
Group:		System Environment/Kernel
Source:		advancecompsquash-%{version}.tar.bz2
Buildroot:	%{_tmppath}/%{name}-%{version}

BuildArchitectures: i586


%description
The compressed loopback block device kernel module
squashfs is the driver module for transparent access to a
ISO9660 filesystem contained in compressed volume.


##
## Setup Section
##

%prep
%setup -q -n advancecompsquash-%{version}


##
## Build Section
##

%build
[ -n "%{buildroot}" -a "%{buildroot}" != / ] && rm -rf %{buildroot}
mkdir -p $RPM_BUILD_ROOT

./configure
make


##
## Install Section
##

%install
strip mksquashfs2

mkdir -p %{buildroot}/opt/berry
install -m 755 mksquashfs2 %{buildroot}/opt/berry

#mkdir -p %{buildroot}/lib/modules/%{kernel_rel}/kernel/drivers/block
#install -m 644 cloop.ko %{buildroot}/lib/modules/%{kernel_rel}/kernel/drivers/block


##
## Clean Section
##

%clean
[ -n "%{buildroot}" -a "%{buildroot}" != / ] && rm -rf %{buildroot}
rm -rf $RPM_BUILD_DIR/%{name}-%{version}


##
## Files Section
##

%files
%defattr (-,root,root)
/opt/berry/mksquashfs2
#/lib/modules/%{kernel_rel}/kernel/drivers/block/cloop.ko


##
## change log
##

%changelog
* Mon Jun 19 2006 Yuichiro Nakada <berry@po.yui.mine.nu>
- Update to 2.2r2
* Mon Jun 13 2005 Yuichiro Nakada <berry@po.yui.mine.nu>
- Create for Berry Linux
