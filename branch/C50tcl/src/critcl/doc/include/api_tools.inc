
The eleven commands in this section provide tools like
[manpage {CriTcl Application}] or similar with
deeper access to the package's internals.

These commands are irrelevant to anybody just
wishing to write a [file .critcl] file.

[list_begin definitions]

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::actualtarget]]

This command returns the platform identifier of the target platform,
i.e. the platform the generated code will be built for. In contrast to
[cmd ::critcl::targetplatform] this is the true target, with any
cross-compilation information resolved.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::buildforpackage] [opt [arg flag]]]

This command signals whether the next file to be build is built for
inclusion into a package or not. If not specified the [arg flag]
defaults to [const true], i.e. building for a package. This disables a
number of things in the backend, namely the linking of that file into
a shared library, and loading such. It is expected that the build
results are later wrapped into a larger collection.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::cnothingtodo] [arg file]]

This command checks whether there is anything to build for [arg file].

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::cresults] [opt [arg file]]]

This command returns the build result information for the specified [arg file].
If no file is specified the information is taken from [cmd {info script}].

The result in question is a Tcl dictionary with the following keys,
and their meanings:

[list_begin definitions]
[def [const clibraries]]
The list of external shared libraries, and/or locations thereof to
link the [arg file] needs for successful linking.

[def [const ldflags]]
The list of linker flags needed by the [arg file] for successful linking.

[def [const license]]
The license the package in the [arg file] is under. A string.

[def [const mintcl]]
The minimum version of Tcl required by the package in the [arg file]
to run successfully. A proper Tcl version number.

[def [const objects]]
The list of object files backing the [arg file], to be linked.

[def [const preload]]
The list of libraries the generated package has to preload to allow
the package in the [arg file] to run successfully.

[def [const tk]]
A boolean indicating whether the package in the [arg file] has to be
linked against Tk or not.

[def [const tsources]]
The list of companion [file .tcl] files to source for the package in
the [file .critcl] [arg file] to run successfully.

[def [const log]]
The build log in case of failure, and [cmd ::critcl::buildforpackage]
having signaled the build of a package. Otherwise the empty string.
[list_end]

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::crosscheck]]

This command checks if the package is configured for cross-compilation
and prints a message to the standard error channel if so.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::error] [arg msg]]

This command is used by the package to report internal errors. The default
implementation simply throws the error.

Tools like the [manpage {CriTcl Application}] are allowed to redefine
this procedure to perform their own way of error reporting. There is
one constraint they are not allowed to change: The procedure must
[emph {not return}] to the caller.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::knowntargets]]

This command returns a list containing the identifiers of all targets
found during the last invokation of [cmd critcl::readconfig].

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::sharedlibext]]

This command returns the file extension used by shared libraries on the
target platform.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::targetconfig]]

This command returns the target identifier chosen to by either system
or user to build code for.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::buildplatform]]

This command returns the platform identifier of the build platform,
i.e. where the package is running on.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::targetplatform]]

This command returns the platform identifier of the target platform,
i.e. the platform the generated code will be built for. In contrast to
[cmd ::critcl::actualtarget] this may be the name of a
cross-compilation target.

[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::cobjects] [opt [arg arg]...]]

This command is like [cmd ::critcl::clibraries], provides the link
step with additional information. Instead of libraries the arguments
are object files however.

Despite this similarity it is not listed in section
[sectref {Control & Interface}] because it is of no use to package
writers. Only tools like the [manpage {CriTcl Application}] have need
of it.

[para] All arguments are interpreted glob patterns. Patterns matching
no file or non-existing files cause the command to throw an error. The
files matching the patterns are made available to the linker when it
is invoked for the current [file .critcl] file. This means that the
files in question are linked together with the object file backing the
[file .critcl] file into a single shared library.

[para] [emph Note] that patterns which are not beginning with an
absolute path are interpreted relative to the directory containing the
current [file .critcl] file.

[para] Multiple invokations of this command accumulate their
information.


[comment ---------------------------------------------------------------------]
[call [cmd ::critcl::scan] [arg path]]

This command is the main entry point to critcl's static code scanner.
Invoked for a single [file .critcl] file it returns a dictionary providing
the following pieces information about it:

[list_begin definitions]
[def version] Package version.
[def org] Author(ing organization).

[def files] List of the companion files. The paths in this list are
all relative to the location (directory) of the input file.

[list_end]

This command and the information it returns can be used by tools to
implement processing modes like the assembly of a directory hierachy
containing a TEA-lookalike buildystem, etc.

[list_end]
