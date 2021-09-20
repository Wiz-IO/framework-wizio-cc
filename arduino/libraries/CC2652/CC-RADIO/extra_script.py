# WizIO 2021 Georgi Angelov
#   http://www.wizio.eu/
#   https://github.com/Wiz-IO

Import('env')
from os.path import join, realpath

global_env = DefaultEnvironment()

src_filter_default = [
    '+<*>', 
    '+<%s*>' % join(env.ti, 'cc13x2_cc26x2', 'rf_patches', 'rf_patch_cpe_ieee_802_15_4.c'),
]
env.Replace(SRC_FILTER = src_filter_default)

