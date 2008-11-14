%define SRCDIR baulk-0.1

Name:		baulk
Version:	0.1
Release:	1%{?dist}
Summary:	Baulk is a cross-platform native application tiling management tool written in Qt4.

Group:		dev
License:	GPL v2
URL:		http://baulk.sf.net
Source:		baulk-0.1.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:	cmake >= 2.6, doxygen, graphviz
Requires:	qt >= 4.4

%description
Baulk is a cross-platform native application tiling management tool written in Qt4. An emphasis is made on making all major components a separate dynamic library, for modularity.

%prep
%setup -q 

%build
cd src
cmake -DCMAKE_INSTALL_PREFIX=/usr .
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
cd src
make install DESTDIR=$RPM_BUILD_ROOT


%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc



%changelog


