# Dockerfile that modifies oraclelinux:6 to create a data volume container
FROM centos:7
MAINTAINER lyre <lyre@poetpalace.org>
RUN mkdir -p /var/www/html
RUN echo "This is the content for file1.html" > /var/www/html/file1.html
RUN echo "This is the content for file2.html" > /var/www/html/file2.html
RUN echo "This is the content for index.html" > /var/www/html/index.html
VOLUME /var/www/html
ENTRYPOINT /usr/bin/tail -f /dev/null
