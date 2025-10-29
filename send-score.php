<?php
header('Content-Type: application/json');

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405);
    die(json_encode(['error' => 'Samo POST metoda je dozvoljena']));
}

// Validacija ulaznih podataka
if (!isset($_POST['name']) || !isset($_POST['score'])) {
    http_response_code(400);
    die(json_encode(['error' => 'Nedostaju name ili score parametri']));
}

$name = trim($_POST['name']);
$score = intval($_POST['score']);
$level = isset($_POST['level']) ? intval($_POST['level']) : 1; // ili neka podrazumevana vrednost


function write_to_json_file($name, $score, $level) {
    $file = 'data.json';
    
    // Provera i kreiranje fajla ako ne postoji
    if (!file_exists($file)) {
        if (file_put_contents($file, '[]') === false) {
            error_log("Greška: Ne mogu da kreiram data.json");
            return false;
        }
        chmod($file, 0644); // Postavi dozvole
    }
    
    // Provera dozvola
    if (!is_writable($file)) {
        error_log("Greška: data.json nije upisiv. Dozvole: " . decoct(fileperms($file)));
        return false;
    }

    // Učitavanje postojećih podataka
    $json = file_get_contents($file);
    if ($json === false) {
        error_log("Greška: Ne mogu da pročitam data.json");
        return false;
    }

    $data = json_decode($json, true);
    if (json_last_error() !== JSON_ERROR_NONE) {
        error_log("Greška: Nevalidan JSON format: " . json_last_error_msg());
        $data = []; // Resetuj ako je korumpiran
    }

    // Dodavanje novog unosa
    $data[] = [
        'name' => htmlspecialchars($name, ENT_QUOTES, 'UTF-8'),
        'score' => $score,
        'level' => $level,
        'timestamp' => date('Y-m-d H:i:s')
    ];

    // Snimanje
    $result = file_put_contents($file, json_encode($data, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE));
    return $result !== false;
}

if (write_to_json_file($name, $score, $level)) 
{
    echo json_encode(['success' => true, 'message' => 'Uspešno sačuvano!']);
} else {
    http_response_code(500);
    echo json_encode(['success' => false, 'message' => 'Greška pri čuvanju!']);
}
?>