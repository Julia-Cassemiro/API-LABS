#include "../include/include.h"

struct mg_mgr mgr;                                

void 	ft_end(int nmb_signal) // encerrar o programa
{
	remove("./log");
	remove("./file");
	mg_mgr_free(&mgr);   
	exit(1);
}


int	ft_cmp (const void *string1, const void *string2) // compare two strings
{
    unsigned char    *s1;
    unsigned char    *s2;
    size_t            i;

    if (!string1 || !string2)
        return (-1);
    s1 = (unsigned char *)string1;
    s2 = (unsigned char *)string2;
    i = 0;
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (0);
}

void 	ft_log(struct mg_http_message *hm, char *message) //Registrar logs em um arquivo
{
	time_t 		now = time(NULL);
	char 		buf_temp[1000];
	char		buf[1000];
	FILE		*log_f = fopen("./log.log", "a+");

	fread(buf, 1000, 1, log_f);
	strcpy(buf_temp, hm->uri.ptr);//path

	char *string_now = ctime(&now); //para termos o horario do request

	fprintf(log_f, "Date: %s", string_now);
	fprintf(log_f, "Method: %s \n", hm->method.ptr);
	fprintf(log_f, "Status: %s \n", message);
	fprintf(log_f, "URI: %s \n", hm->uri.ptr);
	fprintf(log_f, "Proto: %s \n", hm->proto.ptr);

	fclose(log_f);
}

static void init_request(struct mg_connection *c, int ev, void *ev_data, void *init_request_data) {
  if (ev == MG_EV_HTTP_MSG) 
  {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data; //server local dir

	CURL 		*curl;
	CURLcode 	result;
	char 		buf[1000];
	char		new_buf[1000];
	FILE 		*file = fopen("./file", "w");
	int			count;

	bzero(buf, sizeof(char));
    strcpy(buf, "https://excuser.herokuapp.com/v1/excuse");
    strcat(buf, strtok((char *)hm->uri.ptr, " "));
	curl = curl_easy_init(); //init curl
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(curl, CURLOPT_URL, buf);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	result = curl_easy_perform(curl); //executa configurações acima
    if (result != CURLE_OK) //caso n retorne CURLE_OK, fizemos uma request errado.
    {
		char error[100];
		strcpy(error, "400 Bad Request");

		ft_log(hm, error);
		mg_http_reply(c, 500, "Content-Type: application/json\r\n", "%s\n", curl_easy_strerror(result));
        exit(1);
    }
	else
	{
		char ok[100];
		strcpy(ok, "200 OK"); //caso de certo, copio essa string para o char ok
		fclose(file);
		fopen("./file", "r"); //abrimos o arquivo onde armazenamos o retorno da api
		bzero(new_buf, sizeof(new_buf));
		fread(new_buf, 1000, 1, file); //lemos oq esta no arquivo
		ft_log(hm, ok);
		fclose(file);
		mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n", new_buf); // retornando alguma informação no formato JSON
	    curl_easy_cleanup(curl);
	}
	} 

}

int main() {
	struct sigaction action; // struct da lib signal

	memset(&action, 0, sizeof(action));
	action.sa_handler = ft_end;
	sigaction(SIGINT, &action, NULL);
	mg_mgr_init(&mgr); // init manager
	if (mg_http_listen(&mgr, "http://localhost:8000", init_request, &mgr) == NULL) //setup listener
	{
		fprintf(stderr, "Error in inicialization url\n"); //caso de erro na inicialização
		return (1);
	}    // Create listening connection
	for (;;) mg_mgr_poll(&mgr, 1000); // Event loop
  	mg_mgr_free(&mgr);               // Cleanup
  	return 0;                        // Block forever
}