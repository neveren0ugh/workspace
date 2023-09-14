import numpy as np


def m_dw_h():
    dw = np.half(1)
    while np.half(dw) > np.half(0):
        e_last = np.half(dw)
        dw = np.half(dw) / np.half(2)
    return e_last

def m_dw_s():
    dw = np.single(1)
    while np.single(dw) > np.single(0):
        e_last = np.single(dw)
        dw = np.single(dw) / np.single(2)
    return e_last

def m_dw_d():
    dw = np.double(1)
    while np.double(dw) > np.double(0):
        e_last = np.double(dw)
        dw = np.double(dw) / np.double(2)
    return e_last

def m_dw_ld():
    dw = np.longdouble(1)
    while np.longdouble(dw) > np.longdouble(0):
        e_last = np.longdouble(dw)
        dw = np.longdouble(dw) / np.longdouble(2)
    return np.longdouble(e_last)

np.set_printoptions(formatter={'float': '{: 0.8e}'.format})
print(f'Half precision: {m_dw_h()}\nSingle preciosion: {m_dw_s()}\nDouble precision: {m_dw_d()}\nLDouble precision: {m_dw_ld()}\n')