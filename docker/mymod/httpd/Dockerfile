FROM centos:7
MAINTAINER Lyre <lyre@poetpalace.org>
RUN yum install -y httpd && yum clean all
RUN echo "HTTP Server running on guest" > /var/www/html/index.html
EXPOSE 80
ENTRYPOINT /usr/sbin/httpd -D FOREGROUND
