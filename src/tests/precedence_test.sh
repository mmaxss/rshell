#!/bin/sh

(echo aa || echo bb) || (echo cc || echo dd)
(echo aa || echo bb) || (echo cc && echo dd)
(echo aa || echo bb) || (echo cc ; echo dd)

(echo aa || echo bb) ; (echo cc || echo dd)
(echo aa || echo bb) ; (echo cc && echo dd)
(echo aa || echo bb) ; (echo cc ; echo dd)

(echo aa || echo bb) && (echo cc || echo dd)
(echo aa || echo bb) && (echo cc && echo dd)
(echo aa || echo bb) && (echo cc ; echo dd)


(echo aa ; echo bb) || (echo cc || echo dd)
(echo aa ; echo bb) || (echo cc && echo dd)
(echo aa ; echo bb) || (echo cc ; echo dd)

(echo aa ; echo bb) ; (echo cc || echo dd)
(echo aa ; echo bb) ; (echo cc && echo dd)
(echo aa ; echo bb) ; (echo cc ; echo dd)

(echo aa ; echo bb) && (echo cc || echo dd)
(echo aa ; echo bb) && (echo cc && echo dd)
(echo aa ; echo bb) && (echo cc ; echo dd)

(echo aa && echo bb) || (echo cc || echo dd)
(echo aa && echo bb) || (echo cc && echo dd)
(echo aa && echo bb) || (echo cc ; echo dd)

(echo aa && echo bb) ; (echo cc || echo dd)
(echo aa && echo bb) ; (echo cc && echo dd)
(echo aa && echo bb) ; (echo cc ; echo dd)

(echo aa && echo bb) && (echo cc || echo dd)
(echo aa && echo bb) && (echo cc && echo dd)
(echo aa && echo bb) && (echo cc ; echo dd)