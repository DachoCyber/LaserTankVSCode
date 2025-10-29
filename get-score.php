<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');

// Allow both GET and POST methods
if ($_SERVER['REQUEST_METHOD'] !== 'GET' && $_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405);
    die(json_encode(['error' => 'Only GET or POST methods are allowed']));
}

$file = 'data.json';

// Security checks
if (!file_exists($file)) {
    http_response_code(404);
    die(json_encode(['error' => 'Score data not found']));
}

if (!is_readable($file)) {
    http_response_code(403);
    die(json_encode(['error' => 'Cannot read score data']));
}

$json = file_get_contents($file);
if ($json === false) {
    http_response_code(500);
    die(json_encode(['error' => 'Failed to read data']));
}

$data = json_decode($json, true);
if (json_last_error() !== JSON_ERROR_NONE) {
    http_response_code(500);
    die(json_encode(['error' => 'Invalid data format']));
}

// Return sorted data (highest scores first)
usort($data, function($a, $b) {
    return $a['score'] - $b['score'];
});

echo json_encode(array_values($data), JSON_PRETTY_PRINT);
?>