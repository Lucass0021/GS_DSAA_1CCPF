# Sistema de Cadastro e Consulta de Relatos sobre Catástrofes Naturais
```                                                  
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                      
   \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                        
      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                        
         \\\\\\\\\\\\\\\\\\\\\\\\\\\\\                          
           \\\\\\\\\\\\\\\\\\\\\\\\\\                           
              \\\\\\\\\\\\\\\\\\\\\                             
                 \\\\\\\\\\\\\\\\\                              
                   \\\\\\\\\\\\\\                               
                   \\\\\\\\\\\\\                                
                   \\\\\\\\\\\\                                 
                  \\\\\\\\\\\\                                  
                 \\\\\\\\\\\\                                   
                \\\\\\\\\\\\                                    
               \\\\\\\\\\\\                                     
              \\\\\\\\\\\\                                      
              \\\\\\\\\\\\                                      
         `     \\\\\\\\\\\\      `    `                         
            *    \\\\\\\\\\\\  *   *                            
     `    *    *   \\\\\\\\\\\\   *  *   `                      
             *   *   \\\\\\\\\\  *                              
          `    *   * \\\\\\\\\ *   *   `                        
       `    `     *  \\\\\\\\   *   `_____                      
             \ \ \ * \\\\\\\  * /  /\`````\                    
           \ \ \ \  \\\\\\  / / / /  \`````\                    
         \ \ \ \ \ \\\\\\ / / / / |[] | [] |                       
 ```                                                 

Este projeto consiste em um sistema simples para cadastro, armazenamento e consulta de relatos sobre catástrofes naturais ocorridas em um raio de até 10 km de uma base central. O sistema é desenvolvido em linguagem C.

---
## Funcionalidades

- Cadastro de relatos contendo:
  - Nome do registrante
  - CPF (validado)
  - Data (deve ser a data atual)
  - Hora
  - Tipo da catástrofe (ex: terremoto, enchente, etc)
  - Descrição detalhada do ocorrido
  - Coordenadas X e Y do local do ocorrido

- Cálculo da distância Euclidiana entre o ponto (0,0) - base central - e as coordenadas do relato.

- Aceitação somente de relatos dentro do raio de 10 km da base central.

- Listagem dos relatos cadastrados, ordenados por data, do mais recente ao mais antigo.

- Salvamento e carregamento automático dos relatos em arquivo `relato.txt`.
---

## Contribuidores
    Lucas Alves Antunes Almeida - RM: 566362
    Lucca Rosseto Rezende - RM: 564180
    Massayoshi Bando Fogaça e Silva - RM: 561779
