import os
import logging

logger = logging.getLogger (__name__)
logger.setLevel (logging.DEBUG)

ch = logging.StreamHandler ()
ch.setLevel (logging.DEBUG)

formatter = logging.Formatter ('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

ch.setFormatter (formatter)
logger.addHandler (ch)

logger.debug ('hello')
logger.info ('hello')
logger.warn ('hello')


l = logging.getLogger (__name__)
l.info ('hello')
