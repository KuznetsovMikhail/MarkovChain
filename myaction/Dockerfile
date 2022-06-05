FROM jfloff/alpine-python

RUN pip install --upgrade pip
RUN pip install cpplint

ADD cpp_linter.sh /cpp_linter.sh
RUN chmod +x /cpp_linter.sh
ENTRYPOINT ["/cpp_linter.sh"]
