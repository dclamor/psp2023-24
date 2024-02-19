package com.example.demoapi.persona;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import lombok.RequiredArgsConstructor;

@Service
@RequiredArgsConstructor

public class PersonaService {
    @Autowired
    private PersonaRepository personaRepository;

    public void crearPersona(Persona person){
        personaRepository.save(person);
    }
    public boolean borrarPersona(Integer id){
        personaRepository.deleteById(id);
        return true;
    }
    public Optional<Persona> obtenerPersona(Integer id) {
        
        return personaRepository.findById(id);
        
    }

}
