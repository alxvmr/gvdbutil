%set_verify_elf_method skip

Name: gvdbutil
Version: 0.0.1
Release: alt1

Summary: Reading data from GVDB
License: GPLv3+
Group: Other
Url: https://github.com/alxvmr/gvdbutil
BuildArch: noarch

BuildRequires(pre): rpm-macros-cmake
BuildRequires: gcc-c++
BuildRequires: ccmake
BuildRequires: libgvdb-devel pkgconfig(gtk+-2.0)

Source0: %name-%version.tar

%description
The utility is designed to interact with the GVDB binary database.
Provides possibility to get value by key from the specified database,
get all keys and values from the specified database.

%prep
%setup

%build
%cmake
%cmake_build

%install
%cmake_install

%files
%_bindir/%name
%_includedir/%name

%changelog
* Thu Sep 05 2024 Maria Alexeeva <alxvmr@altlinux.org> 0.0.1-alt1
- First build