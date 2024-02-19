package com.example.demoapi.persona;

import org.springframework.web.bind.annotation.RestController;

import io.swagger.v3.oas.annotations.responses.ApiResponses;
import lombok.RequiredArgsConstructor;

import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;




@RestController
@RequestMapping("/persona")
@RequiredArgsConstructor

public class PersonaController {
    @Autowired
    private final PersonaService personaService;
    
    @PostMapping("/crear")
    
    public ResponseEntity<String> insertarPersona(@RequestBody Persona person){
        personaService.crearPersona(person);
        return ResponseEntity.ok("Se ha creado la persona con éxito");
    }
    @PutMapping("borrarPersona/{id}")
    // @ApiResponses{
    //     @ApiResponse(responseCode = "200", description = "Persona borrada correctamente");
    // }
    public ResponseEntity<String> borrarPersona(@PathVariable String id) {
       if(personaService.borrarPersona(Integer.parseInt(id)))
        return ResponseEntity.ok("Se ha borrado la persona correctamente");
       else
        return ResponseEntity.status(201).body("El registro no se ha borrado correctamente");     
    }
    @GetMapping("obtenerPersona/{id}")
    public ResponseEntity<Optional<Persona>> obtenerPersona(@PathVariable String id) {
        return ResponseEntity.ok(personaService.obtenerPersona(Integer.parseInt(id)));
    }
    
}
