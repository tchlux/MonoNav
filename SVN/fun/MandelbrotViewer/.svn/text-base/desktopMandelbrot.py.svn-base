#!usr/bin/python

# ========================================
#        Color chooser file
# ========================================

# tk common colour chooser dialogue
#
# this module provides an interface to the native color dialogue
# available in Tk 4.2 and newer.
#
# written by Fredrik Lundh, May 1997
#
# fixed initialcolor handling in August 1998
#

#
# options (all have default values):
#
# - initialcolor: colour to mark as selected when dialog is displayed
#   (given as an RGB triplet or a Tk color string)
#
# - parent: which window to place the dialog on top of
#
# - title: dialog title
#

from tkinter.commondialog import Dialog


#
# color chooser class

class Chooser(Dialog):
    "Ask for a color"

    command = "tk_chooseColor"

    def _fixoptions(self):
        try:
            # make sure initialcolor is a tk color string
            color = self.options["initialcolor"]
            if isinstance(color, tuple):
                # assume an RGB triplet
                self.options["initialcolor"] = "#%02x%02x%02x" % color
        except KeyError:
            pass

    def _fixresult(self, widget, result):
        # result can be somethings: an empty tuple, an empty string or
        # a Tcl_Obj, so this somewhat weird check handles that
        if not result or not str(result):
            return None, None # canceled

        # to simplify application code, the color chooser returns
        # an RGB tuple together with the Tk color string
        r, g, b = widget.winfo_rgb(result)
        return (r/256, g/256, b/256), str(result)


#
# convenience stuff

def askcolor(color = None, **options):
    "Ask for a color"

    if color:
        options = options.copy()
        options["initialcolor"] = color

    return Chooser(**options).show()



# ========================================
#          messagebox file
# ========================================

# tk common message boxes
#
# this module provides an interface to the native message boxes
# available in Tk 4.2 and newer.
#
# written by Fredrik Lundh, May 1997
#

#
# options (all have default values):
#
# - default: which button to make default (one of the reply codes)
#
# - icon: which icon to display (see below)
#
# - message: the message to display
#
# - parent: which window to place the dialog on top of
#
# - title: dialog title
#
# - type: dialog type; that is, which buttons to display (see below)
#

from tkinter.commondialog import Dialog

#
# constants

# icons
ERROR = "error"
INFO = "info"
QUESTION = "question"
WARNING = "warning"

# types
ABORTRETRYIGNORE = "abortretryignore"
OK = "ok"
OKCANCEL = "okcancel"
RETRYCANCEL = "retrycancel"
YESNO = "yesno"
YESNOCANCEL = "yesnocancel"

# replies
ABORT = "abort"
RETRY = "retry"
IGNORE = "ignore"
OK = "ok"
CANCEL = "cancel"
YES = "yes"
NO = "no"


#
# message dialog class

class Message(Dialog):
    "A message box"

    command  = "tk_messageBox"


#
# convenience stuff

# Rename _icon and _type options to allow overriding them in options
def _show(title=None, message=None, _icon=None, _type=None, **options):
    if _icon and "icon" not in options:    options["icon"] = _icon
    if _type and "type" not in options:    options["type"] = _type
    if title:   options["title"] = title
    if message: options["message"] = message
    res = Message(**options).show()
    # In some Tcl installations, yes/no is converted into a boolean.
    if isinstance(res, bool):
        if res:
            return YES
        return NO
    # In others we get a Tcl_Obj.
    return str(res)

def showinfo(title=None, message=None, **options):
    "Show an info message"
    return _show(title, message, INFO, OK, **options)

def showwarning(title=None, message=None, **options):
    "Show a warning message"
    return _show(title, message, WARNING, OK, **options)

def showerror(title=None, message=None, **options):
    "Show an error message"
    return _show(title, message, ERROR, OK, **options)

def askquestion(title=None, message=None, **options):
    "Ask a question"
    return _show(title, message, QUESTION, YESNO, **options)

def askokcancel(title=None, message=None, **options):
    "Ask if operation should proceed; return true if the answer is ok"
    s = _show(title, message, QUESTION, OKCANCEL, **options)
    return s == OK

def askyesno(title=None, message=None, **options):
    "Ask a question; return true if the answer is yes"
    s = _show(title, message, QUESTION, YESNO, **options)
    return s == YES

def askyesnocancel(title=None, message=None, **options):
    "Ask a question; return true if the answer is yes, None if cancelled."
    s = _show(title, message, QUESTION, YESNOCANCEL, **options)
    # s might be a Tcl index object, so convert it to a string
    s = str(s)
    if s == CANCEL:
        return None
    return s == YES

def askretrycancel(title=None, message=None, **options):
    "Ask if operation should be retried; return true if the answer is yes"
    s = _show(title, message, WARNING, RETRYCANCEL, **options)
    return s == RETRY

# ========================================
#             ttk file
# ========================================

"""Ttk wrapper.

This module provides classes to allow using Tk themed widget set.

Ttk is based on a revised and enhanced version of
TIP #48 (http://tip.tcl.tk/48) specified style engine.

Its basic idea is to separate, to the extent possible, the code
implementing a widget's behavior from the code implementing its
appearance. Widget class bindings are primarily responsible for
maintaining the widget state and invoking callbacks, all aspects
of the widgets appearance lies at Themes.
"""

__version__ = "0.3.1"

__author__ = "Guilherme Polo <ggpolo@gmail.com>"

__all__ = ["Button", "Checkbutton", "Combobox", "Entry", "Frame", "Label",
           "Labelframe", "LabelFrame", "Menubutton", "Notebook", "Panedwindow",
           "PanedWindow", "Progressbar", "Radiobutton", "Scale", "Scrollbar",
           "Separator", "Sizegrip", "Style", "Treeview",
           # Extensions
           "LabeledScale", "OptionMenu",
           # functions
           "tclobjs_to_py", "setup_master"]

import tkinter

_flatten = tkinter._flatten

# Verify if Tk is new enough to not need the Tile package
_REQUIRE_TILE = True if tkinter.TkVersion < 8.5 else False

def _load_tile(master):
    if _REQUIRE_TILE:
        import os
        tilelib = os.environ.get('TILE_LIBRARY')
        if tilelib:
            # append custom tile path to the list of directories that
            # Tcl uses when attempting to resolve packages with the package
            # command
            master.tk.eval(
                    'global auto_path; '
                    'lappend auto_path {%s}' % tilelib)

        master.tk.eval('package require tile') # TclError may be raised here
        master._tile_loaded = True

def _format_optdict(optdict, script=False, ignore=None):
    """Formats optdict to a tuple to pass it to tk.call.

    E.g. (script=False):
      {'foreground': 'blue', 'padding': [1, 2, 3, 4]} returns:
      ('-foreground', 'blue', '-padding', '1 2 3 4')"""
    format = "%s" if not script else "{%s}"

    opts = []
    for opt, value in optdict.items():
        if ignore and opt in ignore:
            continue

        if isinstance(value, (list, tuple)):
            v = []
            for val in value:
                if isinstance(val, str):
                    v.append(str(val) if val else '{}')
                else:
                    v.append(str(val))

            # format v according to the script option, but also check for
            # space in any value in v in order to group them correctly
            value = format % ' '.join(
                ('{%s}' if ' ' in val else '%s') % val for val in v)

        if script and value == '':
            value = '{}' # empty string in Python is equivalent to {} in Tcl

        opts.append(("-%s" % opt, value))

    # Remember: _flatten skips over None
    return _flatten(opts)

def _format_mapdict(mapdict, script=False):
    """Formats mapdict to pass it to tk.call.

    E.g. (script=False):
      {'expand': [('active', 'selected', 'grey'), ('focus', [1, 2, 3, 4])]}

      returns:

      ('-expand', '{active selected} grey focus {1, 2, 3, 4}')"""
    # if caller passes a Tcl script to tk.call, all the values need to
    # be grouped into words (arguments to a command in Tcl dialect)
    format = "%s" if not script else "{%s}"

    opts = []
    for opt, value in mapdict.items():

        opt_val = []
        # each value in mapdict is expected to be a sequence, where each item
        # is another sequence containing a state (or several) and a value
        for statespec in value:
            state, val = statespec[:-1], statespec[-1]

            if len(state) > 1: # group multiple states
                state = "{%s}" % ' '.join(state)
            else: # single state
                # if it is empty (something that evaluates to False), then
                # format it to Tcl code to denote the "normal" state
                state = state[0] or '{}'

            if isinstance(val, (list, tuple)): # val needs to be grouped
                val = "{%s}" % ' '.join(map(str, val))

            opt_val.append("%s %s" % (state, val))

        opts.append(("-%s" % opt, format % ' '.join(opt_val)))

    return _flatten(opts)

def _format_elemcreate(etype, script=False, *args, **kw):
    """Formats args and kw according to the given element factory etype."""
    spec = None
    opts = ()
    if etype in ("image", "vsapi"):
        if etype == "image": # define an element based on an image
            # first arg should be the default image name
            iname = args[0]
            # next args, if any, are statespec/value pairs which is almost
            # a mapdict, but we just need the value
            imagespec = _format_mapdict({None: args[1:]})[1]
            spec = "%s %s" % (iname, imagespec)

        else:
            # define an element whose visual appearance is drawn using the
            # Microsoft Visual Styles API which is responsible for the
            # themed styles on Windows XP and Vista.
            # Availability: Tk 8.6, Windows XP and Vista.
            class_name, part_id = args[:2]
            statemap = _format_mapdict({None: args[2:]})[1]
            spec = "%s %s %s" % (class_name, part_id, statemap)

        opts = _format_optdict(kw, script)

    elif etype == "from": # clone an element
        # it expects a themename and optionally an element to clone from,
        # otherwise it will clone {} (empty element)
        spec = args[0] # theme name
        if len(args) > 1: # elementfrom specified
            opts = (args[1], )

    if script:
        spec = '{%s}' % spec
        opts = ' '.join(map(str, opts))

    return spec, opts

def _format_layoutlist(layout, indent=0, indent_size=2):
    """Formats a layout list so we can pass the result to ttk::style
    layout and ttk::style settings. Note that the layout doesn't has to
    be a list necessarily.

    E.g.:
      [("Menubutton.background", None),
       ("Menubutton.button", {"children":
           [("Menubutton.focus", {"children":
               [("Menubutton.padding", {"children":
                [("Menubutton.label", {"side": "left", "expand": 1})]
               })]
           })]
       }),
       ("Menubutton.indicator", {"side": "right"})
      ]

      returns:

      Menubutton.background
      Menubutton.button -children {
        Menubutton.focus -children {
          Menubutton.padding -children {
            Menubutton.label -side left -expand 1
          }
        }
      }
      Menubutton.indicator -side right"""
    script = []

    for layout_elem in layout:
        elem, opts = layout_elem
        opts = opts or {}
        fopts = ' '.join(map(str, _format_optdict(opts, True, "children")))
        head = "%s%s%s" % (' ' * indent, elem, (" %s" % fopts) if fopts else '')

        if "children" in opts:
            script.append(head + " -children {")
            indent += indent_size
            newscript, indent = _format_layoutlist(opts['children'], indent,
                indent_size)
            script.append(newscript)
            indent -= indent_size
            script.append('%s}' % (' ' * indent))
        else:
            script.append(head)

    return '\n'.join(script), indent

def _script_from_settings(settings):
    """Returns an appropriate script, based on settings, according to
    theme_settings definition to be used by theme_settings and
    theme_create."""
    script = []
    # a script will be generated according to settings passed, which
    # will then be evaluated by Tcl
    for name, opts in settings.items():
        # will format specific keys according to Tcl code
        if opts.get('configure'): # format 'configure'
            s = ' '.join(map(str, _format_optdict(opts['configure'], True)))
            script.append("ttk::style configure %s %s;" % (name, s))

        if opts.get('map'): # format 'map'
            s = ' '.join(map(str, _format_mapdict(opts['map'], True)))
            script.append("ttk::style map %s %s;" % (name, s))

        if 'layout' in opts: # format 'layout' which may be empty
            if not opts['layout']:
                s = 'null' # could be any other word, but this one makes sense
            else:
                s, _ = _format_layoutlist(opts['layout'])
            script.append("ttk::style layout %s {\n%s\n}" % (name, s))

        if opts.get('element create'): # format 'element create'
            eopts = opts['element create']
            etype = eopts[0]

            # find where args end, and where kwargs start
            argc = 1 # etype was the first one
            while argc < len(eopts) and not hasattr(eopts[argc], 'items'):
                argc += 1

            elemargs = eopts[1:argc]
            elemkw = eopts[argc] if argc < len(eopts) and eopts[argc] else {}
            spec, opts = _format_elemcreate(etype, True, *elemargs, **elemkw)

            script.append("ttk::style element create %s %s %s %s" % (
                name, etype, spec, opts))

    return '\n'.join(script)

def _dict_from_tcltuple(ttuple, cut_minus=True):
    """Break tuple in pairs, format it properly, then build the return
    dict. If cut_minus is True, the supposed '-' prefixing options will
    be removed.

    ttuple is expected to contain an even number of elements."""
    opt_start = 1 if cut_minus else 0

    retdict = {}
    it = iter(ttuple)
    for opt, val in zip(it, it):
        retdict[str(opt)[opt_start:]] = val

    return tclobjs_to_py(retdict)

def _list_from_statespec(stuple):
    """Construct a list from the given statespec tuple according to the
    accepted statespec accepted by _format_mapdict."""
    nval = []
    for val in stuple:
        typename = getattr(val, 'typename', None)
        if typename is None:
            nval.append(val)
        else: # this is a Tcl object
            val = str(val)
            if typename == 'StateSpec':
                val = val.split()
            nval.append(val)

    it = iter(nval)
    return [_flatten(spec) for spec in zip(it, it)]

def _list_from_layouttuple(ltuple):
    """Construct a list from the tuple returned by ttk::layout, this is
    somewhat the reverse of _format_layoutlist."""
    res = []

    indx = 0
    while indx < len(ltuple):
        name = ltuple[indx]
        opts = {}
        res.append((name, opts))
        indx += 1

        while indx < len(ltuple): # grab name's options
            opt, val = ltuple[indx:indx + 2]
            if not opt.startswith('-'): # found next name
                break

            opt = opt[1:] # remove the '-' from the option
            indx += 2

            if opt == 'children':
                val = _list_from_layouttuple(val)

            opts[opt] = val

    return res

def _val_or_dict(options, func, *args):
    """Format options then call func with args and options and return
    the appropriate result.

    If no option is specified, a dict is returned. If a option is
    specified with the None value, the value for that option is returned.
    Otherwise, the function just sets the passed options and the caller
    shouldn't be expecting a return value anyway."""
    options = _format_optdict(options)
    res = func(*(args + options))

    if len(options) % 2: # option specified without a value, return its value
        return res

    return _dict_from_tcltuple(res)

def _convert_stringval(value):
    """Converts a value to, hopefully, a more appropriate Python object."""
    value = str(value)
    try:
        value = int(value)
    except (ValueError, TypeError):
        pass

    return value

def tclobjs_to_py(adict):
    """Returns adict with its values converted from Tcl objects to Python
    objects."""
    for opt, val in adict.items():
        if val and hasattr(val, '__len__') and not isinstance(val, str):
            if getattr(val[0], 'typename', None) == 'StateSpec':
                val = _list_from_statespec(val)
            else:
                val = list(map(_convert_stringval, val))

        elif hasattr(val, 'typename'): # some other (single) Tcl object
            val = _convert_stringval(val)

        adict[opt] = val

    return adict

def setup_master(master=None):
    """If master is not None, itself is returned. If master is None,
    the default master is returned if there is one, otherwise a new
    master is created and returned.

    If it is not allowed to use the default root and master is None,
    RuntimeError is raised."""
    if master is None:
        if tkinter._support_default_root:
            master = tkinter._default_root or tkinter.Tk()
        else:
            raise RuntimeError(
                    "No master specified and tkinter is "
                    "configured to not support default root")
    return master


class Style(object):
    """Manipulate style database."""

    _name = "ttk::style"

    def __init__(self, master=None):
        master = setup_master(master)

        if not getattr(master, '_tile_loaded', False):
            # Load tile now, if needed
            _load_tile(master)

        self.master = master
        self.tk = self.master.tk


    def configure(self, style, query_opt=None, **kw):
        """Query or sets the default value of the specified option(s) in
        style.

        Each key in kw is an option and each value is either a string or
        a sequence identifying the value for that option."""
        if query_opt is not None:
            kw[query_opt] = None
        return _val_or_dict(kw, self.tk.call, self._name, "configure", style)


    def map(self, style, query_opt=None, **kw):
        """Query or sets dynamic values of the specified option(s) in
        style.

        Each key in kw is an option and each value should be a list or a
        tuple (usually) containing statespecs grouped in tuples, or list,
        or something else of your preference. A statespec is compound of
        one or more states and then a value."""
        if query_opt is not None:
            return _list_from_statespec(
                self.tk.call(self._name, "map", style, '-%s' % query_opt))

        return _dict_from_tcltuple(
            self.tk.call(self._name, "map", style, *(_format_mapdict(kw))))


    def lookup(self, style, option, state=None, default=None):
        """Returns the value specified for option in style.

        If state is specified it is expected to be a sequence of one
        or more states. If the default argument is set, it is used as
        a fallback value in case no specification for option is found."""
        state = ' '.join(state) if state else ''

        return self.tk.call(self._name, "lookup", style, '-%s' % option,
            state, default)


    def layout(self, style, layoutspec=None):
        """Define the widget layout for given style. If layoutspec is
        omitted, return the layout specification for given style.

        layoutspec is expected to be a list or an object different than
        None that evaluates to False if you want to "turn off" that style.
        If it is a list (or tuple, or something else), each item should be
        a tuple where the first item is the layout name and the second item
        should have the format described below:

        LAYOUTS

            A layout can contain the value None, if takes no options, or
            a dict of options specifying how to arrange the element.
            The layout mechanism uses a simplified version of the pack
            geometry manager: given an initial cavity, each element is
            allocated a parcel. Valid options/values are:

                side: whichside
                    Specifies which side of the cavity to place the
                    element; one of top, right, bottom or left. If
                    omitted, the element occupies the entire cavity.

                sticky: nswe
                    Specifies where the element is placed inside its
                    allocated parcel.

                children: [sublayout... ]
                    Specifies a list of elements to place inside the
                    element. Each element is a tuple (or other sequence)
                    where the first item is the layout name, and the other
                    is a LAYOUT."""
        lspec = None
        if layoutspec:
            lspec = _format_layoutlist(layoutspec)[0]
        elif layoutspec is not None: # will disable the layout ({}, '', etc)
            lspec = "null" # could be any other word, but this may make sense
                           # when calling layout(style) later

        return _list_from_layouttuple(
            self.tk.call(self._name, "layout", style, lspec))


    def element_create(self, elementname, etype, *args, **kw):
        """Create a new element in the current theme of given etype."""
        spec, opts = _format_elemcreate(etype, False, *args, **kw)
        self.tk.call(self._name, "element", "create", elementname, etype,
            spec, *opts)


    def element_names(self):
        """Returns the list of elements defined in the current theme."""
        return self.tk.call(self._name, "element", "names")


    def element_options(self, elementname):
        """Return the list of elementname's options."""
        return self.tk.call(self._name, "element", "options", elementname)


    def theme_create(self, themename, parent=None, settings=None):
        """Creates a new theme.

        It is an error if themename already exists. If parent is
        specified, the new theme will inherit styles, elements and
        layouts from the specified parent theme. If settings are present,
        they are expected to have the same syntax used for theme_settings."""
        script = _script_from_settings(settings) if settings else ''

        if parent:
            self.tk.call(self._name, "theme", "create", themename,
                "-parent", parent, "-settings", script)
        else:
            self.tk.call(self._name, "theme", "create", themename,
                "-settings", script)


    def theme_settings(self, themename, settings):
        """Temporarily sets the current theme to themename, apply specified
        settings and then restore the previous theme.

        Each key in settings is a style and each value may contain the
        keys 'configure', 'map', 'layout' and 'element create' and they
        are expected to have the same format as specified by the methods
        configure, map, layout and element_create respectively."""
        script = _script_from_settings(settings)
        self.tk.call(self._name, "theme", "settings", themename, script)


    def theme_names(self):
        """Returns a list of all known themes."""
        return self.tk.call(self._name, "theme", "names")


    def theme_use(self, themename=None):
        """If themename is None, returns the theme in use, otherwise, set
        the current theme to themename, refreshes all widgets and emits
        a <<ThemeChanged>> event."""
        if themename is None:
            # Starting on Tk 8.6, checking this global is no longer needed
            # since it allows doing self.tk.call(self._name, "theme", "use")
            return self.tk.eval("return $ttk::currentTheme")

        # using "ttk::setTheme" instead of "ttk::style theme use" causes
        # the variable currentTheme to be updated, also, ttk::setTheme calls
        # "ttk::style theme use" in order to change theme.
        self.tk.call("ttk::setTheme", themename)


class Widget(tkinter.Widget):
    """Base class for Tk themed widgets."""

    def __init__(self, master, widgetname, kw=None):
        """Constructs a Ttk Widget with the parent master.

        STANDARD OPTIONS

            class, cursor, takefocus, style

        SCROLLABLE WIDGET OPTIONS

            xscrollcommand, yscrollcommand

        LABEL WIDGET OPTIONS

            text, textvariable, underline, image, compound, width

        WIDGET STATES

            active, disabled, focus, pressed, selected, background,
            readonly, alternate, invalid
        """
        master = setup_master(master)
        if not getattr(master, '_tile_loaded', False):
            # Load tile now, if needed
            _load_tile(master)
        tkinter.Widget.__init__(self, master, widgetname, kw=kw)


    def identify(self, x, y):
        """Returns the name of the element at position x, y, or the empty
        string if the point does not lie within any element.

        x and y are pixel coordinates relative to the widget."""
        return self.tk.call(self._w, "identify", x, y)


    def instate(self, statespec, callback=None, *args, **kw):
        """Test the widget's state.

        If callback is not specified, returns True if the widget state
        matches statespec and False otherwise. If callback is specified,
        then it will be invoked with *args, **kw if the widget state
        matches statespec. statespec is expected to be a sequence."""
        ret = self.tk.call(self._w, "instate", ' '.join(statespec))
        if ret and callback:
            return callback(*args, **kw)

        return bool(ret)


    def state(self, statespec=None):
        """Modify or inquire widget state.

        Widget state is returned if statespec is None, otherwise it is
        set according to the statespec flags and then a new state spec
        is returned indicating which flags were changed. statespec is
        expected to be a sequence."""
        if statespec is not None:
            statespec = ' '.join(statespec)

        return self.tk.splitlist(str(self.tk.call(self._w, "state", statespec)))


class Button(Widget):
    """Ttk Button widget, displays a textual label and/or image, and
    evaluates a command when pressed."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Button widget with the parent master.

        STANDARD OPTIONS

            class, compound, cursor, image, state, style, takefocus,
            text, textvariable, underline, width

        WIDGET-SPECIFIC OPTIONS

            command, default, width
        """
        Widget.__init__(self, master, "ttk::button", kw)


    def invoke(self):
        """Invokes the command associated with the button."""
        return self.tk.call(self._w, "invoke")


class Checkbutton(Widget):
    """Ttk Checkbutton widget which is either in on- or off-state."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Checkbutton widget with the parent master.

        STANDARD OPTIONS

            class, compound, cursor, image, state, style, takefocus,
            text, textvariable, underline, width

        WIDGET-SPECIFIC OPTIONS

            command, offvalue, onvalue, variable
        """
        Widget.__init__(self, master, "ttk::checkbutton", kw)


    def invoke(self):
        """Toggles between the selected and deselected states and
        invokes the associated command. If the widget is currently
        selected, sets the option variable to the offvalue option
        and deselects the widget; otherwise, sets the option variable
        to the option onvalue.

        Returns the result of the associated command."""
        return self.tk.call(self._w, "invoke")


class Entry(Widget, tkinter.Entry):
    """Ttk Entry widget displays a one-line text string and allows that
    string to be edited by the user."""

    def __init__(self, master=None, widget=None, **kw):
        """Constructs a Ttk Entry widget with the parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus, xscrollcommand

        WIDGET-SPECIFIC OPTIONS

            exportselection, invalidcommand, justify, show, state,
            textvariable, validate, validatecommand, width

        VALIDATION MODES

            none, key, focus, focusin, focusout, all
        """
        Widget.__init__(self, master, widget or "ttk::entry", kw)


    def bbox(self, index):
        """Return a tuple of (x, y, width, height) which describes the
        bounding box of the character given by index."""
        return self.tk.call(self._w, "bbox", index)


    def identify(self, x, y):
        """Returns the name of the element at position x, y, or the
        empty string if the coordinates are outside the window."""
        return self.tk.call(self._w, "identify", x, y)


    def validate(self):
        """Force revalidation, independent of the conditions specified
        by the validate option. Returns False if validation fails, True
        if it succeeds. Sets or clears the invalid state accordingly."""
        return bool(self.tk.call(self._w, "validate"))


class Combobox(Entry):
    """Ttk Combobox widget combines a text field with a pop-down list of
    values."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Combobox widget with the parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            exportselection, justify, height, postcommand, state,
            textvariable, values, width
        """
        # The "values" option may need special formatting, so leave to
        # _format_optdict the responsibility to format it
        if "values" in kw:
            kw["values"] = _format_optdict({'v': kw["values"]})[1]

        Entry.__init__(self, master, "ttk::combobox", **kw)


    def __setitem__(self, item, value):
        if item == "values":
            value = _format_optdict({item: value})[1]

        Entry.__setitem__(self, item, value)


    def configure(self, cnf=None, **kw):
        """Custom Combobox configure, created to properly format the values
        option."""
        if "values" in kw:
            kw["values"] = _format_optdict({'v': kw["values"]})[1]

        return Entry.configure(self, cnf, **kw)


    def current(self, newindex=None):
        """If newindex is supplied, sets the combobox value to the
        element at position newindex in the list of values. Otherwise,
        returns the index of the current value in the list of values
        or -1 if the current value does not appear in the list."""
        return self.tk.call(self._w, "current", newindex)


    def set(self, value):
        """Sets the value of the combobox to value."""
        self.tk.call(self._w, "set", value)


class Frame(Widget):
    """Ttk Frame widget is a container, used to group other widgets
    together."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Frame with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            borderwidth, relief, padding, width, height
        """
        Widget.__init__(self, master, "ttk::frame", kw)


class Label(Widget):
    """Ttk Label widget displays a textual label and/or image."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Label with parent master.

        STANDARD OPTIONS

            class, compound, cursor, image, style, takefocus, text,
            textvariable, underline, width

        WIDGET-SPECIFIC OPTIONS

            anchor, background, font, foreground, justify, padding,
            relief, text, wraplength
        """
        Widget.__init__(self, master, "ttk::label", kw)


class Labelframe(Widget):
    """Ttk Labelframe widget is a container used to group other widgets
    together. It has an optional label, which may be a plain text string
    or another widget."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Labelframe with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS
            labelanchor, text, underline, padding, labelwidget, width,
            height
        """
        Widget.__init__(self, master, "ttk::labelframe", kw)

LabelFrame = Labelframe # tkinter name compatibility


class Menubutton(Widget):
    """Ttk Menubutton widget displays a textual label and/or image, and
    displays a menu when pressed."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Menubutton with parent master.

        STANDARD OPTIONS

            class, compound, cursor, image, state, style, takefocus,
            text, textvariable, underline, width

        WIDGET-SPECIFIC OPTIONS

            direction, menu
        """
        Widget.__init__(self, master, "ttk::menubutton", kw)


class Notebook(Widget):
    """Ttk Notebook widget manages a collection of windows and displays
    a single one at a time. Each child window is associated with a tab,
    which the user may select to change the currently-displayed window."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Notebook with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            height, padding, width

        TAB OPTIONS

            state, sticky, padding, text, image, compound, underline

        TAB IDENTIFIERS (tab_id)

            The tab_id argument found in several methods may take any of
            the following forms:

                * An integer between zero and the number of tabs
                * The name of a child window
                * A positional specification of the form "@x,y", which
                  defines the tab
                * The string "current", which identifies the
                  currently-selected tab
                * The string "end", which returns the number of tabs (only
                  valid for method index)
        """
        Widget.__init__(self, master, "ttk::notebook", kw)


    def add(self, child, **kw):
        """Adds a new tab to the notebook.

        If window is currently managed by the notebook but hidden, it is
        restored to its previous position."""
        self.tk.call(self._w, "add", child, *(_format_optdict(kw)))


    def forget(self, tab_id):
        """Removes the tab specified by tab_id, unmaps and unmanages the
        associated window."""
        self.tk.call(self._w, "forget", tab_id)


    def hide(self, tab_id):
        """Hides the tab specified by tab_id.

        The tab will not be displayed, but the associated window remains
        managed by the notebook and its configuration remembered. Hidden
        tabs may be restored with the add command."""
        self.tk.call(self._w, "hide", tab_id)


    def identify(self, x, y):
        """Returns the name of the tab element at position x, y, or the
        empty string if none."""
        return self.tk.call(self._w, "identify", x, y)


    def index(self, tab_id):
        """Returns the numeric index of the tab specified by tab_id, or
        the total number of tabs if tab_id is the string "end"."""
        return self.tk.call(self._w, "index", tab_id)


    def insert(self, pos, child, **kw):
        """Inserts a pane at the specified position.

        pos is either the string end, an integer index, or the name of
        a managed child. If child is already managed by the notebook,
        moves it to the specified position."""
        self.tk.call(self._w, "insert", pos, child, *(_format_optdict(kw)))


    def select(self, tab_id=None):
        """Selects the specified tab.

        The associated child window will be displayed, and the
        previously-selected window (if different) is unmapped. If tab_id
        is omitted, returns the widget name of the currently selected
        pane."""
        return self.tk.call(self._w, "select", tab_id)


    def tab(self, tab_id, option=None, **kw):
        """Query or modify the options of the specific tab_id.

        If kw is not given, returns a dict of the tab option values. If option
        is specified, returns the value of that option. Otherwise, sets the
        options to the corresponding values."""
        if option is not None:
            kw[option] = None
        return _val_or_dict(kw, self.tk.call, self._w, "tab", tab_id)


    def tabs(self):
        """Returns a list of windows managed by the notebook."""
        return self.tk.call(self._w, "tabs") or ()


    def enable_traversal(self):
        """Enable keyboard traversal for a toplevel window containing
        this notebook.

        This will extend the bindings for the toplevel window containing
        this notebook as follows:

            Control-Tab: selects the tab following the currently selected
                         one

            Shift-Control-Tab: selects the tab preceding the currently
                               selected one

            Alt-K: where K is the mnemonic (underlined) character of any
                   tab, will select that tab.

        Multiple notebooks in a single toplevel may be enabled for
        traversal, including nested notebooks. However, notebook traversal
        only works properly if all panes are direct children of the
        notebook."""
        # The only, and good, difference I see is about mnemonics, which works
        # after calling this method. Control-Tab and Shift-Control-Tab always
        # works (here at least).
        self.tk.call("ttk::notebook::enableTraversal", self._w)


class Panedwindow(Widget, tkinter.PanedWindow):
    """Ttk Panedwindow widget displays a number of subwindows, stacked
    either vertically or horizontally."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Panedwindow with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            orient, width, height

        PANE OPTIONS

            weight
        """
        Widget.__init__(self, master, "ttk::panedwindow", kw)


    forget = tkinter.PanedWindow.forget # overrides Pack.forget


    def insert(self, pos, child, **kw):
        """Inserts a pane at the specified positions.

        pos is either the string end, and integer index, or the name
        of a child. If child is already managed by the paned window,
        moves it to the specified position."""
        self.tk.call(self._w, "insert", pos, child, *(_format_optdict(kw)))


    def pane(self, pane, option=None, **kw):
        """Query or modify the options of the specified pane.

        pane is either an integer index or the name of a managed subwindow.
        If kw is not given, returns a dict of the pane option values. If
        option is specified then the value for that option is returned.
        Otherwise, sets the options to the corresponding values."""
        if option is not None:
            kw[option] = None
        return _val_or_dict(kw, self.tk.call, self._w, "pane", pane)


    def sashpos(self, index, newpos=None):
        """If newpos is specified, sets the position of sash number index.

        May adjust the positions of adjacent sashes to ensure that
        positions are monotonically increasing. Sash positions are further
        constrained to be between 0 and the total size of the widget.

        Returns the new position of sash number index."""
        return self.tk.call(self._w, "sashpos", index, newpos)

PanedWindow = Panedwindow # tkinter name compatibility


class Progressbar(Widget):
    """Ttk Progressbar widget shows the status of a long-running
    operation. They can operate in two modes: determinate mode shows the
    amount completed relative to the total amount of work to be done, and
    indeterminate mode provides an animated display to let the user know
    that something is happening."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Progressbar with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            orient, length, mode, maximum, value, variable, phase
        """
        Widget.__init__(self, master, "ttk::progressbar", kw)


    def start(self, interval=None):
        """Begin autoincrement mode: schedules a recurring timer event
        that calls method step every interval milliseconds.

        interval defaults to 50 milliseconds (20 steps/second) if ommited."""
        self.tk.call(self._w, "start", interval)


    def step(self, amount=None):
        """Increments the value option by amount.

        amount defaults to 1.0 if omitted."""
        self.tk.call(self._w, "step", amount)


    def stop(self):
        """Stop autoincrement mode: cancels any recurring timer event
        initiated by start."""
        self.tk.call(self._w, "stop")


class Radiobutton(Widget):
    """Ttk Radiobutton widgets are used in groups to show or change a
    set of mutually-exclusive options."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Radiobutton with parent master.

        STANDARD OPTIONS

            class, compound, cursor, image, state, style, takefocus,
            text, textvariable, underline, width

        WIDGET-SPECIFIC OPTIONS

            command, value, variable
        """
        Widget.__init__(self, master, "ttk::radiobutton", kw)


    def invoke(self):
        """Sets the option variable to the option value, selects the
        widget, and invokes the associated command.

        Returns the result of the command, or an empty string if
        no command is specified."""
        return self.tk.call(self._w, "invoke")


class Scale(Widget, tkinter.Scale):
    """Ttk Scale widget is typically used to control the numeric value of
    a linked variable that varies uniformly over some range."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Scale with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            command, from, length, orient, to, value, variable
        """
        Widget.__init__(self, master, "ttk::scale", kw)


    def configure(self, cnf=None, **kw):
        """Modify or query scale options.

        Setting a value for any of the "from", "from_" or "to" options
        generates a <<RangeChanged>> event."""
        if cnf:
            kw.update(cnf)
        Widget.configure(self, **kw)
        if any(['from' in kw, 'from_' in kw, 'to' in kw]):
            self.event_generate('<<RangeChanged>>')


    def get(self, x=None, y=None):
        """Get the current value of the value option, or the value
        corresponding to the coordinates x, y if they are specified.

        x and y are pixel coordinates relative to the scale widget
        origin."""
        return self.tk.call(self._w, 'get', x, y)


class Scrollbar(Widget, tkinter.Scrollbar):
    """Ttk Scrollbar controls the viewport of a scrollable widget."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Scrollbar with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            command, orient
        """
        Widget.__init__(self, master, "ttk::scrollbar", kw)


class Separator(Widget):
    """Ttk Separator widget displays a horizontal or vertical separator
    bar."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Separator with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus

        WIDGET-SPECIFIC OPTIONS

            orient
        """
        Widget.__init__(self, master, "ttk::separator", kw)


class Sizegrip(Widget):
    """Ttk Sizegrip allows the user to resize the containing toplevel
    window by pressing and dragging the grip."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Sizegrip with parent master.

        STANDARD OPTIONS

            class, cursor, state, style, takefocus
        """
        Widget.__init__(self, master, "ttk::sizegrip", kw)


class Treeview(Widget, tkinter.XView, tkinter.YView):
    """Ttk Treeview widget displays a hierarchical collection of items.

    Each item has a textual label, an optional image, and an optional list
    of data values. The data values are displayed in successive columns
    after the tree label."""

    def __init__(self, master=None, **kw):
        """Construct a Ttk Treeview with parent master.

        STANDARD OPTIONS

            class, cursor, style, takefocus, xscrollcommand,
            yscrollcommand

        WIDGET-SPECIFIC OPTIONS

            columns, displaycolumns, height, padding, selectmode, show

        ITEM OPTIONS

            text, image, values, open, tags

        TAG OPTIONS

            foreground, background, font, image
        """
        Widget.__init__(self, master, "ttk::treeview", kw)


    def bbox(self, item, column=None):
        """Returns the bounding box (relative to the treeview widget's
        window) of the specified item in the form x y width height.

        If column is specified, returns the bounding box of that cell.
        If the item is not visible (i.e., if it is a descendant of a
        closed item or is scrolled offscreen), returns an empty string."""
        return self.tk.call(self._w, "bbox", item, column)


    def get_children(self, item=None):
        """Returns a tuple of children belonging to item.

        If item is not specified, returns root children."""
        return self.tk.call(self._w, "children", item or '') or ()


    def set_children(self, item, *newchildren):
        """Replaces item's child with newchildren.

        Children present in item that are not present in newchildren
        are detached from tree. No items in newchildren may be an
        ancestor of item."""
        self.tk.call(self._w, "children", item, newchildren)


    def column(self, column, option=None, **kw):
        """Query or modify the options for the specified column.

        If kw is not given, returns a dict of the column option values. If
        option is specified then the value for that option is returned.
        Otherwise, sets the options to the corresponding values."""
        if option is not None:
            kw[option] = None
        return _val_or_dict(kw, self.tk.call, self._w, "column", column)


    def delete(self, *items):
        """Delete all specified items and all their descendants. The root
        item may not be deleted."""
        self.tk.call(self._w, "delete", items)


    def detach(self, *items):
        """Unlinks all of the specified items from the tree.

        The items and all of their descendants are still present, and may
        be reinserted at another point in the tree, but will not be
        displayed. The root item may not be detached."""
        self.tk.call(self._w, "detach", items)


    def exists(self, item):
        """Returns True if the specified item is present in the tree,
        False otherwise."""
        return bool(self.tk.call(self._w, "exists", item))


    def focus(self, item=None):
        """If item is specified, sets the focus item to item. Otherwise,
        returns the current focus item, or '' if there is none."""
        return self.tk.call(self._w, "focus", item)


    def heading(self, column, option=None, **kw):
        """Query or modify the heading options for the specified column.

        If kw is not given, returns a dict of the heading option values. If
        option is specified then the value for that option is returned.
        Otherwise, sets the options to the corresponding values.

        Valid options/values are:
            text: text
                The text to display in the column heading
            image: image_name
                Specifies an image to display to the right of the column
                heading
            anchor: anchor
                Specifies how the heading text should be aligned. One of
                the standard Tk anchor values
            command: callback
                A callback to be invoked when the heading label is
                pressed.

        To configure the tree column heading, call this with column = "#0" """
        cmd = kw.get('command')
        if cmd and not isinstance(cmd, str):
            # callback not registered yet, do it now
            kw['command'] = self.master.register(cmd, self._substitute)

        if option is not None:
            kw[option] = None

        return _val_or_dict(kw, self.tk.call, self._w, 'heading', column)


    def identify(self, component, x, y):
        """Returns a description of the specified component under the
        point given by x and y, or the empty string if no such component
        is present at that position."""
        return self.tk.call(self._w, "identify", component, x, y)


    def identify_row(self, y):
        """Returns the item ID of the item at position y."""
        return self.identify("row", 0, y)


    def identify_column(self, x):
        """Returns the data column identifier of the cell at position x.

        The tree column has ID #0."""
        return self.identify("column", x, 0)


    def identify_region(self, x, y):
        """Returns one of:

        heading: Tree heading area.
        separator: Space between two columns headings;
        tree: The tree area.
        cell: A data cell.

        * Availability: Tk 8.6"""
        return self.identify("region", x, y)


    def identify_element(self, x, y):
        """Returns the element at position x, y.

        * Availability: Tk 8.6"""
        return self.identify("element", x, y)


    def index(self, item):
        """Returns the integer index of item within its parent's list
        of children."""
        return self.tk.call(self._w, "index", item)


    def insert(self, parent, index, iid=None, **kw):
        """Creates a new item and return the item identifier of the newly
        created item.

        parent is the item ID of the parent item, or the empty string
        to create a new top-level item. index is an integer, or the value
        end, specifying where in the list of parent's children to insert
        the new item. If index is less than or equal to zero, the new node
        is inserted at the beginning, if index is greater than or equal to
        the current number of children, it is inserted at the end. If iid
        is specified, it is used as the item identifier, iid must not
        already exist in the tree. Otherwise, a new unique identifier
        is generated."""
        opts = _format_optdict(kw)
        if iid:
            res = self.tk.call(self._w, "insert", parent, index,
                "-id", iid, *opts)
        else:
            res = self.tk.call(self._w, "insert", parent, index, *opts)

        return res


    def item(self, item, option=None, **kw):
        """Query or modify the options for the specified item.

        If no options are given, a dict with options/values for the item
        is returned. If option is specified then the value for that option
        is returned. Otherwise, sets the options to the corresponding
        values as given by kw."""
        if option is not None:
            kw[option] = None
        return _val_or_dict(kw, self.tk.call, self._w, "item", item)


    def move(self, item, parent, index):
        """Moves item to position index in parent's list of children.

        It is illegal to move an item under one of its descendants. If
        index is less than or equal to zero, item is moved to the
        beginning, if greater than or equal to the number of children,
        it is moved to the end. If item was detached it is reattached."""
        self.tk.call(self._w, "move", item, parent, index)

    reattach = move # A sensible method name for reattaching detached items


    def next(self, item):
        """Returns the identifier of item's next sibling, or '' if item
        is the last child of its parent."""
        return self.tk.call(self._w, "next", item)


    def parent(self, item):
        """Returns the ID of the parent of item, or '' if item is at the
        top level of the hierarchy."""
        return self.tk.call(self._w, "parent", item)


    def prev(self, item):
        """Returns the identifier of item's previous sibling, or '' if
        item is the first child of its parent."""
        return self.tk.call(self._w, "prev", item)


    def see(self, item):
        """Ensure that item is visible.

        Sets all of item's ancestors open option to True, and scrolls
        the widget if necessary so that item is within the visible
        portion of the tree."""
        self.tk.call(self._w, "see", item)


    def selection(self, selop=None, items=None):
        """If selop is not specified, returns selected items."""
        return self.tk.call(self._w, "selection", selop, items)


    def selection_set(self, items):
        """items becomes the new selection."""
        self.selection("set", items)


    def selection_add(self, items):
        """Add items to the selection."""
        self.selection("add", items)


    def selection_remove(self, items):
        """Remove items from the selection."""
        self.selection("remove", items)


    def selection_toggle(self, items):
        """Toggle the selection state of each item in items."""
        self.selection("toggle", items)


    def set(self, item, column=None, value=None):
        """With one argument, returns a dictionary of column/value pairs
        for the specified item. With two arguments, returns the current
        value of the specified column. With three arguments, sets the
        value of given column in given item to the specified value."""
        res = self.tk.call(self._w, "set", item, column, value)
        if column is None and value is None:
            return _dict_from_tcltuple(res, False)
        else:
            return res


    def tag_bind(self, tagname, sequence=None, callback=None):
        """Bind a callback for the given event sequence to the tag tagname.
        When an event is delivered to an item, the callbacks for each
        of the item's tags option are called."""
        self._bind((self._w, "tag", "bind", tagname), sequence, callback, add=0)


    def tag_configure(self, tagname, option=None, **kw):
        """Query or modify the options for the specified tagname.

        If kw is not given, returns a dict of the option settings for tagname.
        If option is specified, returns the value for that option for the
        specified tagname. Otherwise, sets the options to the corresponding
        values for the given tagname."""
        if option is not None:
            kw[option] = None
        return _val_or_dict(kw, self.tk.call, self._w, "tag", "configure",
            tagname)


    def tag_has(self, tagname, item=None):
        """If item is specified, returns 1 or 0 depending on whether the
        specified item has the given tagname. Otherwise, returns a list of
        all items which have the specified tag.

        * Availability: Tk 8.6"""
        return self.tk.call(self._w, "tag", "has", tagname, item)


# Extensions

class LabeledScale(Frame):
    """A Ttk Scale widget with a Ttk Label widget indicating its
    current value.

    The Ttk Scale can be accessed through instance.scale, and Ttk Label
    can be accessed through instance.label"""

    def __init__(self, master=None, variable=None, from_=0, to=10, **kw):
        """Construct an horizontal LabeledScale with parent master, a
        variable to be associated with the Ttk Scale widget and its range.
        If variable is not specified, a tkinter.IntVar is created.

        WIDGET-SPECIFIC OPTIONS

            compound: 'top' or 'bottom'
                Specifies how to display the label relative to the scale.
                Defaults to 'top'.
        """
        self._label_top = kw.pop('compound', 'top') == 'top'

        Frame.__init__(self, master, **kw)
        self._variable = variable or tkinter.IntVar(master)
        self._variable.set(from_)
        self._last_valid = from_

        self.label = Label(self)
        self.scale = Scale(self, variable=self._variable, from_=from_, to=to)
        self.scale.bind('<<RangeChanged>>', self._adjust)

        # position scale and label according to the compound option
        scale_side = 'bottom' if self._label_top else 'top'
        label_side = 'top' if scale_side == 'bottom' else 'bottom'
        self.scale.pack(side=scale_side, fill='x')
        tmp = Label(self).pack(side=label_side) # place holder
        self.label.place(anchor='n' if label_side == 'top' else 's')

        # update the label as scale or variable changes
        self.__tracecb = self._variable.trace_variable('w', self._adjust)
        self.bind('<Configure>', self._adjust)
        self.bind('<Map>', self._adjust)


    def destroy(self):
        """Destroy this widget and possibly its associated variable."""
        try:
            self._variable.trace_vdelete('w', self.__tracecb)
        except AttributeError:
            # widget has been destroyed already
            pass
        else:
            del self._variable
            Frame.destroy(self)


    def _adjust(self, *args):
        """Adjust the label position according to the scale."""
        def adjust_label():
            self.update_idletasks() # "force" scale redraw

            x, y = self.scale.coords()
            if self._label_top:
                y = self.scale.winfo_y() - self.label.winfo_reqheight()
            else:
                y = self.scale.winfo_reqheight() + self.label.winfo_reqheight()

            self.label.place_configure(x=x, y=y)

        from_, to = self.scale['from'], self.scale['to']
        if to < from_:
            from_, to = to, from_
        newval = self._variable.get()
        if not from_ <= newval <= to:
            # value outside range, set value back to the last valid one
            self.value = self._last_valid
            return

        self._last_valid = newval
        self.label['text'] = newval
        self.after_idle(adjust_label)


    def _get_value(self):
        """Return current scale value."""
        return self._variable.get()


    def _set_value(self, val):
        """Set new scale value."""
        self._variable.set(val)


    value = property(_get_value, _set_value)


class OptionMenu(Menubutton):
    """Themed OptionMenu, based after tkinter's OptionMenu, which allows
    the user to select a value from a menu."""

    def __init__(self, master, variable, default=None, *values, **kwargs):
        """Construct a themed OptionMenu widget with master as the parent,
        the resource textvariable set to variable, the initially selected
        value specified by the default parameter, the menu values given by
        *values and additional keywords.

        WIDGET-SPECIFIC OPTIONS

            style: stylename
                Menubutton style.
            direction: 'above', 'below', 'left', 'right', or 'flush'
                Menubutton direction.
            command: callback
                A callback that will be invoked after selecting an item.
        """
        kw = {'textvariable': variable, 'style': kwargs.pop('style', None),
              'direction': kwargs.pop('direction', None)}
        Menubutton.__init__(self, master, **kw)
        self['menu'] = tkinter.Menu(self, tearoff=False)

        self._variable = variable
        self._callback = kwargs.pop('command', None)
        if kwargs:
            raise tkinter.TclError('unknown option -%s' % (
                next(iter(kwargs.keys()))))

        self.set_menu(default, *values)


    def __getitem__(self, item):
        if item == 'menu':
            return self.nametowidget(Menubutton.__getitem__(self, item))

        return Menubutton.__getitem__(self, item)


    def set_menu(self, default=None, *values):
        """Build a new menu of radiobuttons with *values and optionally
        a default value."""
        menu = self['menu']
        menu.delete(0, 'end')
        for val in values:
            menu.add_radiobutton(label=val,
                command=tkinter._setit(self._variable, val, self._callback))

        if default:
            self._variable.set(default)


    def destroy(self):
        """Destroy this widget and its associated variable."""
        del self._variable
        Menubutton.destroy(self)



# ========================================
#           Begin PPM class
# ========================================


import math

ROW_LOC = 1
COL_LOC = 2

#These are typical color constants.
#You can use these, but they aren't required.
BLACK = (0,0,0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
CYAN = (0, 255, 255)
MAGENTA = (255, 0, 255)
YELLOW = (255, 255, 0)

#Default constants
WIDTH = 640
HEIGHT = 480

class PPM:
    #Constructor
    #Pre:  Parameters rows and cols are two integers, representing image size
    #Post: Creates a list to represent the image internally.  Defaults the
    #      image.
    def __init__(self, width=WIDTH, height=HEIGHT):
        self._image_list = []
        self.reset_image(width, height)

    #Pre:  Parameters rows and cols are two integers representing
    #      the rows and columns of the image.
    #Post: Sets the _img_list attribute to a new list of tuples that is 
    #      rows x cols in size, all pixels are white
    def reset_image(self, cols, rows):
        self._image_list = [[WHITE for i in range(cols)] for i in range(rows)]

    #Pre:  Parameter location is a tuple, representing a 2-d coordinate in the
    #      image.  Parameter color is a 3-tuple, representing an RGB value
    #      to write to the specified pixel.
    #Post: Sets the self._image_list attribute at x,y to be color.
    def draw_pixel(self, location, color):
        y_loc, x_loc = location
        try:
            self._image_list[x_loc][y_loc] = color
        except IndexError:
            print("Caught Exception: Either x =", x_loc, "or y =", y_loc,
                  "is out of range.")

    #Pre:  Parameters start_loc and end_loc are tuples, representing
    #      2-d coordinates in the image.
    #      Parameter color is a 3-tuple, representing RGB values
    #      to use for the line color.
    #Post: Writes a color line into self._image_list from start_loc to end_loc
    def draw_line(self, start_loc, end_loc, color):
        if start_loc == end_loc:
            return

        start_y, start_x = start_loc
        end_y, end_x = end_loc

        delta_x = abs(end_x - start_x)
        delta_y = abs(end_y - start_y)

        sx = -1
        if start_x < end_x:
            sx = 1

        sy = -1
        if start_y < end_y:
            sy = 1
        
        err = delta_x - delta_y

        cx = start_x
        cy = start_y
        go_on = True
        while go_on:
            try:
                self._image_list[cx][cy] = color
            except IndexError:
                print("Either", cx, "or", cy, "is out of range")
            go_on = not(cx == end_x and cy == end_y)

            error = 2*err
            if error > -delta_y:
                err -= delta_y
                cx += sx

            if error < delta_x:
                err += delta_x
                cy += sy

    #Remember, any attributes or methods that begin with an "_" are
    #"Private", and should not be used externally from the class.
    #Pre:  f_obj is a valid file object we can write to.
    #      a_list is the list of tuples we want to write to the file.
    #Post: writes the tuples to the file separated by spaces, with a new line at
    #      the end.
    def _write_list(self, f_obj, a_list):
        for tup in a_list:
            f_obj.write(bytes(tup))

    #Opens a file and writes the list to the file PPM style
    #Pre:  Parameter file_name is a valid string of a file we
    #      have access to write to.
    #Post: writes the self._image_list attribute to the
    #      specified file in PPM format, and closes the file.
    def save_image(self, file_name):
        try:
            f = open(file_name, "wb")

            #The PPM file magic number!
            f.write(bytes("P6 ",'UTF-8'))

            #Row and column information
            f.write(bytes(str(len(self._image_list[0])) + " " +
                    str(len(self._image_list)) + " ", "UTF-8"))

            #Color Information
            f.write(bytes("255\n","UTF-8"))
            
            for row in self._image_list:
                self._write_list(f, row)

        except IOError:
            print("Exception: Error opening file", file_name)
        finally:
            f.close()


# ========================================
#          mandelbrot file
# ========================================

import threading
import time
IMAGE_FILE = "MandelbrotTemp.ppm"
NUM_THREADS = 1
SLEEP_TIME = .05

#This class will hold all of the necessary equations for a mandelbrot image.
class Mandelbrot:
    # Pre:  The function to call and the arg to pass it
    # Post: Threading class used for threading
    class myThread(threading.Thread):
        def __init__(self, run, arg):
            self.exe = run
            self.args = arg
            threading.Thread.__init__(self)
        def run(self):
            self.exe(self.args)


    #Constructor, this method will initialize all attributes and start
    #the process of calculating a mandelbrot image
    #Pre:   The mandelbrot class is created
    #Post:  The attributes are created and the process begins
    def __init__(self, parent):
        self.parent = parent #parent viewing window class
        self.lows = []  #list of len 3 for [red, green, blue] lows
        self.mids = []  #list of len 3 for [red, green, blue] mids
        self.highs = [] #list of len 3 for [red, green, blue] highs
        self.depth = 0  #maximum depth of calculation
        self.dim = 0    #ppm image dimensions
        self.a = 0.0    #complex a coord
        self.b = 0.0    #complex b coord
        self.hsize = 0.0 #half of mandelbrot size (zoom ratio)
        self.counter = 0 #counter for knowing how many pixels have
                         #been calculated
        self.ppm = None  #holder for ppm image class

        self.update_formulas() 

    # Pre:  a -------> floating point value for complex a coord
    #       b -------> floating point value for complex b coord
    #       size ----> integer number of pixel width
    #       dim  ---->  
    #       red/g/b -> lists of length three rerpresenting
    #                  [low, medium, high] values for each color
    #       depth ---> integer value for max calculation depth
    # Post: each corresponding value is updated
    def set(self, a, b, size, dimensions, red,green,blue , depth):
        self.a, self.b, self.hsize = a, b, float(size/2)
        self.dim = dimensions
        self.lows = [red[0], green[0], blue[0]]
        self.mids = [red[1], green[1], blue[1]]
        self.highs = [red[2], green[2], blue[2]]
        self.depth = depth

        del(self.ppm)
        self.ppm = PPM(width=self.dim, height=self.dim)

    #Method:This updates the formulas for x and y complex number algorithms
    #Pre:   called
    #Att's: self.a (type=Float)
    #       self.b (type=Float)
    #       self.hsize (type=Int)
    #Post:  
    def update_formulas(self):
        #These equations are used to convert pixels coordinates to
        #complex coordinates
        self.min_x = (self.a - self.hsize)
        self.min_y = (self.b - self.hsize)
        self.x_diff = (self.a+self.hsize) - self.min_x
        self.y_diff = (self.b+self.hsize) - self.min_y
        self.x_complex = lambda x: x/self.dim * (self.x_diff) + self.min_x
        self.y_complex = lambda y: y/self.dim * (self.y_diff) + self.min_y


    #This method converts complex coordinates to pixel coordinates
    #Pre:   The a and b values of the complex numer
    #Post:  Two numbers that are the corresponding pixel coordinates
    def convert_to_pixel_coord(self, x, y):
        pixx = self.dim/2 + ((x-2)/4)*self.dim
        pixy = self.dim/2 + ((y-2)/4)*self.dim
        return pixx, pixy

    #Method:Interpolates between two values with a percentage given
    #Pre:   The two values as three-length tuples and the percentage
    #Att's: None
    #Post:  The (r,g,b) tuple of integers
    def interpolate(self, c1, c2, i):
        return (int((1-i)*c1[0] + i*c2[0]), int((1-i)*c1[1] + i*c2[1]), int((1-i)*c1[2] + i*c2[2]))

    #Method:Calculates the depth of a given pixel coordinate
    #Pre:   The x,y euclydian coord is given
    #Att's: self.x_complex (type=equation)
    #       self.y_complex (type=equation)
    #Post:  The depth achieved is returned
    def calc_depth(self, x, y):
        init = complex(self.x_complex(x), self.y_complex(y))
        cnum = init
        depth = 0
        while depth<self.depth:
            cnum = cnum*cnum + init
            if abs(cnum) > 2:
                return depth
            depth += 1
        return depth

    # Pre:  Called
    # Post: The appropriate number of threads are created and ran
    def configure_threads(self):
        name = "thread"
        for i in range(NUM_THREADS):
            start = int((self.dim/NUM_THREADS) * i)
            setattr(self, name+chr(i), self.myThread(self.calculate,start))
            thread = getattr(self, name+chr(i))
            thread.start()

    # Pre:  start is the beginning y pixel location to start at
    # Post: This portion of the mandelbrot image is generated
    def calculate(self, start=0):
        end = int(start + self.dim / NUM_THREADS)
        for y in range(start, end):
            self.counter += 1 #increment count
            for x in range(self.dim):
                depth = self.calc_depth(x,y)
                if depth <= self.depth//2:
                    c = depth/(self.depth//2)
                    (r,g,b) = self.interpolate(self.lows,self.mids,c)
                else:
                    c = (depth-self.depth//2)/self.depth
                    (r,g,b) = self.interpolate(self.mids, self.highs,c)
                self.ppm.draw_pixel((x,y),(r,g,b))

    # Pre:  
    # Post: if any threads are alive at all
    def threads_alive(self):
        alive = False
        name = "thread"
        for i in range(NUM_THREADS):
            thread = getattr(self, name+chr(i))
            alive = alive or thread.is_alive()
        return alive

    # Pre:  
    # Post: The information in parent is updated after the new image
    #       is saved to IMAGE_FILE
    def save_and_update_root(self):
        string = IMAGE_FILE
        self.ppm.save_image(string)
        self.parent.update_picture(None)
        self.parent.statbar["value"] = 0
        self.parent.statbar.grid_forget()
        self.parent.root.informme["text"] = self.parent.inform

    #This method will create the mandelbrot image
    #Pre:   The method is called
    #Post:  The Mandelbrot image is made and written to a file
    def mandelbrot(self):
        self.counter = 0
        self.update_formulas()
        self.configure_threads()
        while self.threads_alive():
            self.parent.statbar["value"] = self.counter
            self.parent.root.update_idletasks()
            time.sleep(SLEEP_TIME)
        self.save_and_update_root()



# ========================================
#        Beginning of tk viewer
# ========================================

import tkinter as tk #for viewing window
import os #to check if a path exists

CANVAS_WH = 300
DIM = 100
DEPTH = 255
A = -.5
B = 0
SIZE = 2
FINE_FACTOR = 3
MOVE_FACTOR = 15
INIT_R = [0, 110, 255]
INIT_G = [5, 170, 15]
INIT_B = [30, 250, 50]
IMAGE_FILENAME = "MandelbrotTemp.ppm"

        # ========================================
        #            Expansion class
        # ========================================

#This class is used to create each viewing window for the users
class SubFrame(tk.Frame):
    #This method adds a child button to the self
    #Pre:    The name of the button, grid x,y, and the associated command are given
    #Post:   The button is drawn to the frame
    def add_button(self, name="Button", gridx=0, gridy=0, com=None, px=50, py=40, cspan=1):
        a = tk.Button(master=self, text=name, command=com, padx=px, pady=py, bg="black", fg="white", activebackground="dark grey")
        a.grid(column=gridx, row=gridy, columnspan=cspan)
        setattr(self, "button"+name, a)

    #This method adds a child label object to the self
    #Pre:    The name of the label, and the grid x,y are given
    #Post:   The label is drawn to the frame
    def add_label(self, name, gridx, gridy, cspan=1, px=1, py=3):
        a = tk.Label(master=self, text=name, padx=px, pady=py, fg="white", bg="black")
        a.grid(column=gridx, row=gridy, columnspan=cspan)
        setattr(self, "label", a)

    # ========================================
    #        Primary viewing window
    # ========================================

class ViewingWindow:
    #Method:Constructor for the coolest application ever
    #Pre:   The Viewing window is initialized if this is the __main__
    #Post:  The application runs
    def __init__(self):
        #configure necesities for mandelbrot
        self.dim = DIM
        self.depth = DEPTH
        self.a = A
        self.b = B
        self.size = SIZE
        self.red = INIT_R
        self.green = INIT_G
        self.blue = INIT_B
        self.fine = FINE_FACTOR

        self.man = Mandelbrot(self)

        self.configure_root()
        self.configure_mainframe()
        self.configure_zoombuttonframe()
        self.configure_statbar()
        self.configure_colorpanel()
        self.configure_interactivepanel()
        self.configure_controlpanal()

        #begin the vicious cycle
        self.run_mandelbrot()
        self.root.mainloop()

        # ========================================
        #          Configuration methods
        # ========================================

    # Pre:  
    # Post: self.root is configured appropriately
    def configure_root(self):
        self.root = tk.Tk()
        self.root.title("Mandelbrot Image Viewer")
        self.root.configure(bg="black")
        w, h = self.root.winfo_screenwidth(), self.root.winfo_screenheight()
        self.root.geometry("%dx%d+%d+%d" % (w//2, h//2, w//4, h//4))
        self.root.bind("<Return>", self.update_picture)
        self.root.bind("<Up>", self.up)
        self.root.bind("<Down>", self.down)
        self.root.bind("<Left>", self.left)
        self.root.bind("<Right>", self.right)
        self.root.bind("<o>", self.zoomout)
        self.root.bind("<i>", self.zoomin)
        self.inform = ""
        self.root.informme = tk.Label(text=self.inform, bg="black", fg="white")
        self.root.informme.grid(column=0, row=2)
        self.root.informme["text"] = ""

    # Pre:  
    # Post: The status bar is initialized and configured
    def configure_statbar(self):
        self.statbar = Progressbar(self.root, orient="horizontal", length=200, mode="determinate")
        self.statbar["value"] = 0
        self.statbar["maximum"] = self.dim
        self.statbar.grid(row=1,column=0)

    #Method:This is what builds the picture and the navigation buttons
    #Pre:   called
    #Post:  mainframe is put on the screen
    def configure_mainframe(self):
        self.mainframe = SubFrame(master=self.root, bg="black")
        self.mainframe.columnconfigure(0, weight=1)
        self.mainframe.columnconfigure(1, weight=2)
        self.mainframe.columnconfigure(2, weight=1)
        self.mainframe.add_button("Left", 0, 1, self.left, 5)
        self.mainframe.add_button("Right", 2, 1, self.right, 5)
        self.mainframe.add_button("Up", 1, 0, self.up, 40, 7)
        self.mainframe.add_button("Down", 1, 2, self.down, 40, 7)
        self.mainframe.grid(column=0, row=0)

        self.picture = tk.Canvas(master=self.mainframe, width=CANVAS_WH,
                                 height=CANVAS_WH, bg="black")
        self.picture.grid(row=1, column=1)
        self.photoImage = None

    #Method:This is the subframe that controls zooming
    #Pre:   The method is called
    #Post:  The zoom buttons (in/out) are grid()ed
    def configure_zoombuttonframe(self):
        self.zoombuttonframe = SubFrame(master=self.root, bg="black")
        self.zoombuttonframe.add_button("Zoom in  ", 0, 0, self.zoomin, 20, 8)
        self.zoombuttonframe.add_button("Zoom out", 0, 1, self.zoomout, 20, 8)
        self.zoombuttonframe.grid(column=1, row=0, sticky="nw")

    #Method:This creates the control panel for changing the colors
    #Pre:   called
    #Post:  The from/to buttons are .grid()ed
    def configure_colorpanel(self):
        self.colorframe = SubFrame(master=self.root, bg="black")
        self.colorframe.add_label("\nCOLOR CONTROL!", 0, 0, cspan=2)
        self.colorframe.add_button("f", 0, 1, self.adjust_color_from, 5, 5, 1)
        self.colorframe.add_button("b", 0, 2, self.adjust_color_between, 5, 5, 2)
        self.colorframe.add_button("t", 1, 1, self.adjust_color_to, 5, 5, 1)
        self.colorframe.buttonf.configure(text="From", bg="#00051e")
        self.colorframe.buttonb.configure(text="Between", bg="#6eaafa")
        self.colorframe.buttont.configure(text="  To  ", bg="#ff0f32")
        self.colorframe.grid(column=1, row=0, sticky="ne")

    #Method:This is called frequently to offer direct movement
    #Pre:   called
    #Post:  the interactivepanelframe is removed and then recreated (inefficient but effective)
    def configure_interactivepanel(self):
        self.interactivepanelframe = SubFrame(master=self.root, bg="black")
        self.interactivepanelframe.add_label("Pixel Count: ", 0, 0)
        self.interactivepanelframe.add_label("Max depth  : ", 0, 1)
        self.interactivepanelframe.add_label("Move to a  : ", 0, 2)
        self.interactivepanelframe.add_label("Move to b  : ", 0, 3)
        self.interactivepanelframe.add_label("Curr. Size : ", 0, 4)
        self.interactivepanelframe.add_label("Fine factor: ", 0, 5)
 
        self.isize = tk.StringVar(value=str(self.dim))
        self.depthtk = tk.StringVar(value=str(self.depth))
        self.complexa = tk.StringVar(value=str(self.a))
        self.complexb = tk.StringVar(value=str(self.b))
        self.size_e = tk.StringVar(value=str(self.size))
        self.fine_factor = tk.StringVar(value=str(self.fine))

        self.isize_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.isize, fg="white", bg="black")
        self.depthtk_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.depthtk, fg="white", bg="black")
        self.complexa_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.complexa, fg="white", bg="black")
        self.complexb_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.complexb, fg="white", bg="black")
        self.size_e_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.size_e, fg="white", bg="black")
        self.fine_factor_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.fine_factor, fg="white", bg="black")

        self.isize_entry.grid(row=0, column=1)
        self.depthtk_entry.grid(row=1, column=1)
        self.complexa_entry.grid(row=2, column=1)
        self.complexb_entry.grid(row=3, column=1)
        self.size_e_entry.grid(row=4, column=1)
        self.fine_factor_entry.grid(row=5, column=1)

        self.interactivepanelframe.add_button("Adjust picture", 0, 6, self.adjust_image, 5, 5, 2)
        self.interactivepanelframe.grid(column=1, row=0, sticky="e")

    # Pre:  
    # Post: controlpanel is created, currently only containts one button
    def configure_controlpanal(self):
        self.controlpanelframe = SubFrame(master=self.root, bg="black")
        self.controlpanelframe.add_button("Save These\n Coordiantes.", 0, 0, self.print_coord, 3, 1)
        self.controlpanelframe.grid(column=1, row=0, sticky="s")

        # ========================================
        #          Color chooser methods
        # ========================================

    #Method:This method changes the self attributes for color lows in the mandelbrot
    #Pre:   from button is pressed and ok is pressed on colorchooser
    #Post:  the button changes colors correspondingly with the image
    def adjust_color_from(self):
        try:
            ((self.red[0],self.green[0],self.blue[0])
             ,string) = askcolor((self.red[0],self.green[0],self.blue[0]))
            self.colorframe.buttonf.configure(bg=string)
            self.run_mandelbrot()
        except TypeError:
            print("You're adopted.")


    #Method:This method changes the self attributes for color mids in the mandelbrot
    #Pre:   to button is pressed and ok is pressed on colorchooser
    #Post:  the button changes colors correspondingly with the image
    def adjust_color_between(self):
        try:
            ((self.red[1],self.green[1],self.blue[1])
             ,string) = askcolor((self.red[1],self.green[1],self.blue[1]))
            self.colorframe.buttonb.configure(bg=string)
            self.run_mandelbrot()
        except TypeError:
            print("Yeah, that was kinda gross...")

    #Method:This method changes the self attributes for color highs in the mandelbrot
    #Pre:   to button is pressed and ok is pressed on colorchooser
    #Post:  the button changes colors correspondingly with the image
    def adjust_color_to(self):
        try:
            ((self.red[2],self.green[2],self.blue[2])
             ,string) = askcolor((self.red[2],self.green[2],self.blue[2]))
            self.colorframe.buttont.configure(bg=string)
            self.run_mandelbrot()
        except TypeError:
            print("What?? I liked that color!")

        # ========================================
        #          Runtime update methods
        # ========================================

    # Pre:  
    # Post: The interactive panel is updated with the newest
    #       information regarding the mandelbrot set
    def update_interactivepanel(self):
        self.isize_entry.delete(0, tk.END)
        self.depthtk_entry.delete(0, tk.END)
        self.complexa_entry.delete(0, tk.END)
        self.complexb_entry.delete(0, tk.END)
        self.size_e_entry.delete(0, tk.END)
        self.fine_factor_entry.delete(0, tk.END)

        self.isize_entry.insert(0,self.dim)
        self.depthtk_entry.insert(0,self.depth)
        self.complexa_entry.insert(0,self.a)
        self.complexb_entry.insert(0,self.b)
        self.size_e_entry.insert(0,self.size)
        self.fine_factor_entry.insert(0,self.fine)

    #Method:This method draws the picture to the canvas provided
    #Pre:   called
    #Post:  the mandelbrot image is loaded on the canvas
    def update_picture(self, null):
        del(self.photoImage)
        self.photoImage = tk.PhotoImage(file=IMAGE_FILENAME)
        loc = (CANVAS_WH/2)#+ (self.dim/2)
        self.picture.create_image(loc, loc, image=self.photoImage)

        # ========================================
        #           Mandelbrot update
        # ========================================

    #Method:This methd is used to call mandelbrot and make images
    #Pre:   called
    #Post:  mandelbrot is made based on self attributes stored earlier on and all frames are updated
    def run_mandelbrot(self):
        self.man.set(self.a, self.b, self.size, self.dim,
                     self.red, self.green, self.blue, self.depth)
        # self.pthread = threading.Thread(target=self.man.run)
        # self.pthread.start()
        self.statbar.grid()
        self.statbar["maximum"] = self.dim
        self.update_interactivepanel()
        self.man.mandelbrot()
        self.update_picture(None)

        # ========================================
        #         Button-binded functions
        # ========================================

    #Method:This method is used when the adjust image button is pressed
    #Pre:   Adjust image button pressed
    #Post:  The mandelbrot is remade accordingly
    def adjust_image(self):
        self.dim = int(self.isize.get())
        self.depth = int(self.depthtk.get())
        self.a = float(self.complexa.get())
        self.b = float(self.complexb.get())
        self.size = float(self.size_e.get())
        self.fine = float(self.fine_factor.get())

        self.isize.set(value=self.dim)
        self.depthtk.set(value=self.depth)
        self.complexa.set(value=self.a)
        self.complexb.set(value=self.b)
        self.size_e.set(value=self.size)
        self.fine_factor.set(value=self.fine)

        self.run_mandelbrot()

    #Method:Zooms in by factor of 3
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def zoomin(self, event=None):
        self.size /= self.fine
        self.run_mandelbrot()

    #Method:Zooms out by factor of 3
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def zoomout(self, event=None):
        self.size *= self.fine
        self.run_mandelbrot()

    #Method:moves image left
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def left(self, event=None):
        move = (self.size*self.fine) / MOVE_FACTOR
        self.a -= move
        self.run_mandelbrot()

    #Method:moves image right
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def right(self, event=None):
        move = (self.size*self.fine) / MOVE_FACTOR
        self.a += move
        self.run_mandelbrot()

    #Method:moves image up
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def up(self, event=None):
        move = (self.size*self.fine) / MOVE_FACTOR
        self.b -= move
        self.run_mandelbrot()

    #Method:moves image down
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def down(self, event=None):
        move = (self.size*self.fine) / MOVE_FACTOR
        self.b += move
        self.run_mandelbrot()

    #Method:Prints the current coordinates to a datafile
    #Pre:   called
    #Post:  messagebox saying operation complete
    def print_coord(self):
        current_file = ''
        if os.path.exists('data.txt'):
            with open('data.txt', 'r') as f:
                current_file = f.read()
                f.close
        with open('data.txt', 'w') as f:
            current_file += "\n________DATA_________\n#A = "+str(self.a)+"\n#B = "+str(self.b)+"\n#SIZE = "+str(self.size)+"\n"
            f.write(current_file)
            f.close
        showwarning(title="All done :)", message="Your current location was saved to data.txt!")


if __name__ == "__main__":
    v = ViewingWindow()
