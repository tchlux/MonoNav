#cd ~/thlux/ #intentionally not using ~ so that emacs opens terminals to
            #current dirctory

#git specific
alias cg="git commit -m"
alias ag="git add"
alias sg="git status"
alias pg="git push -u MonoNav master"

#svn specific
alias u="svn update"
alias c="svn commit -m"
alias s="svn stat"
alias a="svn add"

#extras
alias pd="pushd"
alias po="popd"
alias util="cd ~/thlux/util/"

#emacs easy access
alias code="emacs --font \"DejaVu Sans Mono 11\""
alias o="emacs -nw"

#custom scripts
alias srm="~/bin/softRm"
alias get="~/bin/get"
alias cpdir="~/bin/cpdir"
alias google="~/bin/google.sh"
alias clean="~/bin/clean"
alias cs="ssh thlux@cs.roanoke.edu"
alias cscp="scp thlux@cs.roanoke.edu:"

alias d="sudo mount -t vboxsf Dropbox ~/Dropbox/"

alias trash="pd ~/.local/share/Trash/"