(add-to-list 'load-path "~/thlux/bin/") ;location of fill-column-indicator.el 

(require 'fill-column-indicator) ;imports fci
(add-hook 'after-change-major-mode-hook 'fci-mode) ;activates fci

(autoload 'glsl-mode "glsl-mode" nil t)
(add-to-list 'auto-mode-alist '("\\.vert\\'" . glsl-mode))
(add-to-list 'auto-mode-alist '("\\.frag\\'" . glsl-mode))
 
(setq-default auto-fill-function 'do-auto-fill) ;;start in auto fill
(setq column-number-mode t) ;;show col number
(blink-cursor-mode 0)
(scroll-bar-mode 0)
(tool-bar-mode 0)
(menu-bar-mode 0)
;; (when window-system
;;   (set-cursor-color "white")
;;   (set-background-color "#00002f")
;;   (set-foreground-color "#e0e0e0")
;; )

(setq auto-mode-alist ;;make .h files defalut to c++ mode
      (cons '("\\.h\\'" . c++-mode) auto-mode-alist)) 

(setq start_print "std::cerr << ") ;; Default start_print value
(setq print_delim " << ") ;; Default delimeter value
(setq print_end   " << std::endl;") ;; Default end_print value

;=================================
;     M-x Emacs Command Links     
;=================================

;Pre:  C-c x
;Post: Compile shortcut
(global-set-key (kbd "C-c x") 'compile)
(lookup-key (current-global-map) (kbd "C-c x")) ;;create compile shorcut

;Pre:  C-c a
;Post: Align reg-expression funciton is called
(global-set-key (kbd "C-c a") 'align-regexp)
(lookup-key (current-global-map) (kbd "C-c a")) ;;align regexp shortcut

;===================
;     Utilities     
;===================

;Pre:  count is an integer > 0, character is some string
;Post: string is inserted count times in the current file
(defun insert-string (count string)
  (setq i 0)
  (while (< i count)
    (insert string)
    (setq i (+ 1 i))))

;Pre:  C-c c
;      The new comment-start & comment-end characters are given by the
;      user when prompted
;Post: The variables for comment-start and comment-end are set
;      accordingly
(defun set_comment_characters()
  (interactive)
  (setq comment-start  (read-from-minibuffer "New comment-start character? "))
  (setq comment-end  (read-from-minibuffer "New comment-end character? "))
  (message "Comment characters set for current buffer"))
(global-set-key (kbd "C-c c") 'set_comment_characters)
(lookup-key (current-global-map) (kbd "C-c c"))

;=========================
;     Comment Related     
;=========================

;Pre:  C-c C-a
;Post: A simple arrow is drawn with the start and end comment characters
(defun simple-arrow()
  (interactive) (insert comment-start "-> " comment-end))
(global-set-key (kbd "C-c C-a") 'simple-arrow)
(lookup-key (current-global-map) (kbd "C-c C-a"))

;Pre:  C-c i
;Post: A simple cerr line, blank with cursor in middle
(defun simple_print ()
  (interactive)
  (insert "std::cerr << \"\" << std::endl;") (indent-for-tab-command)
  (backward-char 15))
(global-set-key (kbd "C-c i") 'simple_print)
(lookup-key (current-global-map) (kbd "C-c i"))

;Pre:  C-c n 
;Post: Pre and Post sections are placed and commented out, cursor is
;      moved to end of first line
(defun pre_post ()
  (interactive)
  (insert comment-start "Pre:  " comment-end) (indent-for-tab-command)
  (insert "\n" comment-start "Post: " comment-end) (indent-for-tab-command)
  (previous-line) (move-end-of-line 1) ;;the '1' is for current line
  (message "If you want different comment characters, use C-c c\nmanually set goal column for comments by typing  C-x ;"))
(global-set-key (kbd "C-c n") 'pre_post)
(lookup-key (current-global-map) (kbd "C-c n"))

;Pre:  C-c f
;Post: A flower box is inserted and the cursor is placed in the middle
(defun flower_box()
  (setq title  (read-from-minibuffer "Title of pretty flowerbox? "))
  (interactive)
  (insert comment-start)
  (insert-string (+ (length title) 10) "=")  (insert comment-end "\n")
  (insert comment-start) (insert-string 5 " ") (insert title)
  (insert-string 5 " ")  (insert comment-end "\n")
  (insert comment-start) (insert-string (+ (length title) 10) "=")
  (insert comment-end "\n") (previous-line 3) (end-of-line)
  (indent-for-tab-command) (next-line) (indent-for-tab-command)
  (next-line) (indent-for-tab-command) (next-line))
(global-set-key (kbd "C-c f") 'flower_box)
(lookup-key (current-global-map) (kbd "C-c f"))

;=======================================
;     Standard Use Coding Shortcuts     
;=======================================

;Pre:  M-{
;Post: Open and close curly brackets are placed, the cursor is put in
;      the middle and tabbed over
(defun open_close_curly ()
  (interactive)
  (insert "{\n\n}") (indent-for-tab-command) 
  (previous-line)  (indent-for-tab-command))
(global-set-key (kbd "M-{") 'open_close_curly)
(lookup-key (current-global-map) (kbd "M-{"))

;Pre:  C-c e
;Post: A cerr statement is placed, cursor moved to middle
(defun insert_cerr_line()
  (interactive)
  (indent-for-tab-command)
  (insert "std::cerr << \"")(insert (buffer-name) " ")
  (insert (what-line))(insert ": \" << std::endl;")
  (backward-char 15))
(global-set-key (kbd "C-c e") 'insert_cerr_line)
(lookup-key (current-global-map) (kbd "C-c e"))

;Pre:  C-c p
;Post: A prompt for a variable name, then the print statement for
;      posting that variable to the terminal
(defun print_vars()
  (interactive)
  (setq variable (read-from-minibuffer "Variable name: "))
  (insert start_print) (insert "\"") (insert variable)
  (insert ": \"") (insert print_delim) (insert variable)
  (insert print_end) (indent-for-tab-command))
(global-set-key (kbd "C-c p") 'print_vars)
(lookup-key (current-global-map) (kbd "C-c p"))

;Pre:  C-c o
;Post: A cout statement is placed, cursor moved to middle
(defun insert_big_O_line()
  (interactive)
  (indent-for-tab-command)
  (insert comment-start "Big O class: O()" comment-end)
  (setq i 0)
  (backward-char))
  ;; (while < i (length comment-end))
  ;; (do backward-char' (+ i 1))   (backward-char))
(global-set-key (kbd "C-c o") 'insert_big_O_line)
(lookup-key (current-global-map) (kbd "C-c o"))

;=================================
;     Extra Functions for Fun     
;=================================

;Pre:  C-c s
;Post: The window is split horizontally, a shell is created with the
;      appropriate "cd" command to travel to this file
(defun shell-me()
  (interactive)
  ;; Does the auto start up of the shell, pretty convenient!
  (split-window-horizontally)  ; Split so windows are side-by-side
  (other-window 1)             ; Move 1 window over, to the right buffer
  (setq pathName buffer-file-name) ; Get the path name to this file
  (shell)			     ; Create a shell
  (if (not (equal pathName nil))
      (insert "cd " pathName))) ; insert cd for ease if filename exists
(global-set-key (kbd "C-c s") 'shell-me)
(lookup-key (current-global-map) (kbd "C-c s")) ;;create shortcut

;Pre:  C-x x
;Post: The given util path file is found
(defun find_util_file ()
  (interactive)
  (find-file "~/thlux/util/"))
(global-set-key (kbd "C-x x") 'find_util_file)
(lookup-key (current-global-map) (kbd "C-x x"))


;================================
;     Old Outdated Functions     
;================================

;;(defun turn-on-flyspell () (flyspell-mode 1))(add-hook 'find-file-hooks 'turn-on-flyspell)

;; ;Pre:  count is an integer > 0, function is callable wout params
;; ;Post: function is called count times
;; (defun repeat-funct (count function)
;;   (setq i 0)
;;   (while (< i count)
;;     (function())
;;     (setq i (+ 1 i))
;;     )
;;   )

;; ;Pre:  
;; ;Post: 
;; (defun functionconditions ()
;;  "This inserts the noting stuff for functions"
;;  (interactive)
;;  (insert "#Pre:  \n#Post: "))
;; (global-set-key (kbd "C-c f") 'functionconditions)
;; (lookup-key (current-global-map) (kbd "C-c f"))

;; (defun methodconditions ()
;;  "This inserts the noting stuff for methods"
;;  (interactive)
;;  (insert "    #Method:\n    #Pre:   \n    #Post:  "))
;; (global-set-key (kbd "C-c m") 'methodconditions)
;; (lookup-key (current-global-map) (kbd "C-c m"))

;; (defun classconditions ()
;;  "This inserts the noting stuff for classes"
;;  (interactive)
;;  (insert "#Class:   \n#Runtime: \n#Mainloop:"))
;; (global-set-key (kbd "C-c c") 'classconditions)
;; (lookup-key (current-global-map) (kbd "C-c c"))

;; (defun new_note_line_method ()
;;  "This inserts the noting stuff for methods"
;;  (interactive)
;;  (insert "    #       "))
;; (global-set-key (kbd "C-c n") 'new_note_line_method)
;; (lookup-key (current-global-map) (kbd "C-c n"))

;; (defun python-syntax_check ()
;;    "Runs a python syntax check"
;;    (interactive)
;;    (shell-command (concat "python -m py_compile " (buffer-name))))
;; (global-set-key (kbd "C-x c") 'python-syntax_check)
;; (lookup-key (current-global-map) (kbd "C-x c"))

;; (defun delete_auto_file()
;;   "This function will delete the auto file that may already exist"
;;   (condition-case nil
;;       (delete-file "Auto-compiled")
;;     (error nil)))

;; (defun compile_c()
;;   "This program will compile the current c file into it's executable
;;   form with a generic name and run it."
;;   (interactive)
;;   (delete_auto_file)
;;   (shell-command (concat "gcc " (buffer-file-name) " -o Auto-compiled -lglut -lGLU -lGL")))
;; (global-set-key (kbd "C-x C-a") 'compile_c)
;; (lookup-key (current-global-map) (kbd "C-x C-a"))

;; (defun execute_auto_file()
;;   "Execution of the compiled c file"
;;   (interactive)
;;   (shell-command "./Auto-compiled")
;;   (delete_auto_file)
;;   )
;; (global-set-key (kbd "C-q") 'execute_auto_file)
;; (lookup-key (current-global-map) (kbd "C-q"))

;; (defun svn_resolve ()
;;   "Exectues resolved on the current file"
;;   (interactive)
;;   (shell-command (concat "svn resolved " (buffer-file-name))))
;; (global-set-key (kbd "C-x v r") 'svn_resolve)
;; (lookup-key (current-global-map) (kbd "C-x v r"))

;; (defun find_beacon()
;;   "This will find the nearest beacon using the search command"
;;   (interactive)
;;   (re-search-forward "##BEACON:  BEEP  BEEP##"))
;; (global-set-key (kbd "C-c b") 'find_beacon)
;; (lookup-key (current-global-map) (kbd "C-c b"))

;; (defun beacon ()
;;  "This inserts an easy to find sequence"
;;  (interactive)
;;  (insert "##BEACON:  BEEP  BEEP##\n"))
;; (global-set-key (kbd "C-c v") 'beacon)
;; (lookup-key (current-global-map) (kbd "C-c v"))

;; (defun cancelsave ()
;;  "Nonce function"
;;  (interactive)
;;  (message "You've really got to stop doing that."))
;; (global-set-key (kbd "C-x C-g") 'cancelsave)
;; (lookup-key (current-global-map) (kbd "C-x C-g"))

;; (defun test_method ()
;;  "This inserts the noting stuff for a test method"
;;  (interactive)
;;  (insert "    #Purpose:      \n    #Ideal in/out: "))
;; (global-set-key (kbd "C-c t") 'test_method)
;; (lookup-key (current-global-map) (kbd "C-c t"))

