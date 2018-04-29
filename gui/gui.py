import tkinter as tk
import tkinter.ttk as ttk
from subprocess import Popen, PIPE, STDOUT

from stops import StopsId, StopsName


stops_id = sorted(list(StopsId.values()))


class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)

        self.grid(row=4, column=0)
        self.create_cb_start()
        self.create_cb_destination()
        self.create_set_station()
        self.start = ""
        self.destination = ""
        self.procces = None

    def create_cb_start(self):
        self.cb_start = ttk.Combobox(root, values=(stops_id))
        self.cb_start.set("Stacja Początkowa")
        self.cb_start.grid(row=0, column=0)
        self.cb_start.bind('<<ComboboxSelected>>', self.st_select)

    def create_cb_destination(self):
        self.cb_destination = ttk.Combobox(root, values=(stops_id))
        self.cb_destination.set("Stacja Końcowa")
        self.cb_destination.grid(row=1, column=0)
        self.cb_destination.bind('<<ComboboxSelected>>', self.ds_select)

    def create_set_station(self):
        self.hi_there = tk.Button(self)
        self.hi_there["text"] = "Wyznacz Trasę"
        self.hi_there["command"] = self.set_the_route
        self.hi_there.grid(row=2, column=0)

    def st_select(self, event=None):
        if event:
            self.start = StopsName[event.widget.get()]

    def ds_select(self, event=None):
        if event:
            self.destination = StopsName[event.widget.get()]

    def set_the_route(self):

        if self.start and self.destination:
            self.procces= Popen(['../bin/PAMSI_2'], stdin=PIPE)
            bin_input = str(self.start) + '\n' + str(self.destination) + '\n'
            b_bin_input = bin_input.encode(encoding='utf-8',errors='strict')
            selfp_stdout = self.procces.communicate(input=b_bin_input)[0]
            self.procces.kill()


root = tk.Tk()
app = Application(master=root)
app.master.title("Jak (prawdopodobnie) dojadę")
app.mainloop()
